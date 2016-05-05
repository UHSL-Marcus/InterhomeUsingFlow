/********************************************************************
// *************************** XMLUtil.cpp **************************
/*******************************************************************/

#include "XMLUtil.h"
#include <iostream>

using namespace pugi;
using std::cout;

/****-----XML Parse -----****/

/******Public Functions *****/

XMLParse::XMLParse(string _source) {
	
	source = _source;
}

string XMLParse::getSource() {
	return source;
}

bool XMLParse::getStringNode(string path, string* out) {
	//cout << "((New Node || Path: " << path;
	bool success = false;
	string text;
	
	xml_document doc;
	if (GetDocument(doc)) {
		//cout << " || doc exists: " << source;
		xpath_node node = doc.select_node(path.c_str());
		
		if (node) {
			text = node.node().child_value();
			//cout << " || node text: " << text;
			if (text.size() > 0) {
				*out = string(text);
				success = true;
			}
		}
	}
	
	//cout << "))";
	return success;
	
}

bool XMLParse::getStringNodes(string path, vector<string>& out) {
	//cout << "((New Node || Path: " << path;
	bool success = false;
	string text;
	
	xml_document doc;
	if (GetDocument(doc)) {
		//cout << " || doc exists: " << source;
		xpath_node_set nodes = doc.select_nodes(path.c_str());
		
		if (nodes.first()) {
			for (xpath_node_set::const_iterator itr = nodes.begin(); itr != nodes.end(); ++itr) {
				xpath_node node = *itr;
				text = node.node().child_value();
				if (text.size() > 0) {
					out.push_back(text);
					success = true;
				}
			}
		}
	}
	
	//cout << "))";
	return success;
	
}

bool nextChildNodeXML(xml_node &node, string &outXML) {
	//cout << "\n\nNext Child";
	bool success = false;
	
	xml_node_type nodeType = node.type();
	
	if (nodeType == node_document || nodeType == node_element) {
		
		for (xml_node child = node.first_child(); child; child = child.next_sibling())
		{
			if (child.type() == node_pcdata) {
				//cout << "\ntext element";
				outXML += child.value();
				//cout << "\noutput: " << outXML;
				success = true;
			} else {
				//cout << "\nnode element";
				outXML += string("<") + string(child.name()) + string(">");
				//cout << "\noutput: " << outXML;
				success = nextChildNodeXML(child, outXML);
				outXML += string("</") + string(child.name()) + string(">");
				//cout << "\noutput: " << outXML;
			}
		}

	}
	
	return success;
}
bool XMLParse::getNodeXML(string path, string &out) {
	//cout << "\n\nNode XML, path: " << path;
	bool success = false;
	
	xml_document doc;
	if (GetDocument(doc)) {
		//cout << "\n got doc";
		xpath_node xNode = doc.select_node(path.c_str());
		
		if (xNode) {
			//cout << "\ngot xNode";
			xml_node node = xNode.node();
			
			if (node) {
				//cout << "\ngot node";
				success = nextChildNodeXML(node, out);
			}
			
		}

	}
	
	return success;
}

bool XMLParse::getNodesXML(string path, vector<string> &out) {
	//cout << "\n\nNode XML, path: " << path;
	bool success = false;
	
	xml_document doc;
	if (GetDocument(doc)) {
		//cout << "\n got doc";
		xpath_node_set xNodes = doc.select_nodes(path.c_str());
		
		if (xNodes.first()) {
			for (xpath_node_set::const_iterator itr = xNodes.begin(); itr != xNodes.end(); ++itr) {
				xpath_node xNode = *itr;
				xml_node node = xNode.node();
				
				if (node) {
					//cout << "\ngot node";
					string tempXML;
					success = nextChildNodeXML(node, tempXML);
					if (success)
						out.push_back(tempXML);
				}
			}
		}

	}
	
	return success;
}

bool nextChildsplitXML(xml_node &node, vector<pair<string, string> > &out ,string path = "") {
	//cout << "\n\nNext Child (" << node.name() << ")\nPath: " << path;
	bool success = false;
	xml_node_type nodeType = node.type();
	
	if (nodeType == node_document || nodeType == node_element) {
		//cout << "\nDoc or Element";
		
		if (nodeType == node_element)
			path += string(node.name()) + string("/");
		
		//cout << "\nnew path: '" << path << "'";
		
		for (xml_node child = node.first_child(); child; child = child.next_sibling())
		{
			//cout << "\n\n---interation---";
			if (child.type() == node_pcdata) {
				//cout << "\nText element\nPath: " << path.substr(0, path.size()-1) << ", text: " << child.value();
				out.push_back(std::make_pair(path.substr(0, path.size()-1) ,string(child.value())));
				//cout << "\nvector count: " << out.size();
				success = true;
			} else {
				//cout << "\nanother child";
				success = nextChildsplitXML(child, out, path);
			}
		}
	}
	//cout << "\nSuccess: " << success;
	return success;
} 
bool XMLParse::splitXML(vector<pair<string, string> > &out) {
	bool success = false;
	
	xml_document doc;
	if (GetDocument(doc)) {
		success = nextChildsplitXML(doc, out);
	}
	return success;
}



/******Private Functions *****/



bool XMLParse::GetDocument(xml_document& returnDoc) {
	
	bool success = false;
	
	size_t size = strlen(source.c_str());
	char* buffer = static_cast<char*>(get_memory_allocation_function()(size));
	memcpy(buffer, source.c_str(), size);
	

	xml_parse_result result = returnDoc.load_buffer_inplace_own(buffer, size);
	
	if (result) {
		success = true;
	}
	
	return success;
}



/****-----XML Build -----****/

/******Public Functions *****/
XMLBuild::XMLBuild(string root) {
		xmlString = "<" + root + "></" + root + ">";
}
XMLBuild::XMLBuild() {
	
}

bool XMLBuild::addStringNode(string path, string text) {
	
	//cout << "\n\nAdding string node. Path: " << path << ", text: " << text;
	bool success = false;
	//cout << "\nxmlstring: " << xmlString;
	
	vector<string> nodeNames;
	size_t current;
	size_t next = -1;
	do
	{
	  current = next + 1;
	  next = path.find_first_of('/', current);
	  nodeNames.push_back(path.substr(current, next - current));
	}
	while (next != string::npos);
	
	if (xmlString.size() < 1) { // if the string is blank then the XML document was inialised with no root node
		xmlString = "<" + nodeNames[0] + "></" + nodeNames[0] + ">"; // add the first node to the string so the document has something to work with
	}
	
	xml_document doc;
	if (GetDocument(doc)) {
		//cout << "\ngot doc";
		
		if (nodeNames.size() > 0) {
			//cout << "\nsplit node names";
			
			// loop through and append any nodes requires for the path
			xml_node currentNode = doc;
			for (int i = 0; i < nodeNames.size(); i++) {
				//cout << "\ncurrent node name: " << currentNode.name();
				xml_node nextNode = currentNode.child(nodeNames[i].c_str());
				if (!nextNode) {
					//cout << "\ncreating nextNode (" << nodeNames[i] << ")";
					nextNode = currentNode.append_child(nodeNames[i].c_str());
				}
				currentNode = nextNode;
			}
			currentNode.append_child(node_pcdata).set_value(text.c_str());
			
			std::stringstream ss;
			doc.save(ss);
			
			xmlString = ss.str();
			
			success = true;
		}
	}
	
	return success;
}

bool XMLBuild::addXML(string path, string xml) {
	//cout << "\n\nAddXML (" << xml << "), path: " << path;
	bool success = false;
	
	XMLParse xmlParse(xml);
	vector<pair<string, string> > xmlVector;
	if (xmlParse.splitXML(xmlVector)) {
		//cout << "\nXML split";
		
		for (int i = 0; i < xmlVector.size(); i++) {
			//cout << "\nXML path: " << path + string("/") + xmlVector[i].first << ", text: "  << xmlVector[i].second;
			if (addStringNode(path + string("/") + xmlVector[i].first, xmlVector[i].second)) {
				success = true;
			} else { success = false; break; }
		}
	}
	
	return success;
}

bool XMLBuild::removeNode(string path) {
	//cout << "\n\nRemove node, path: " << path;
	bool success = false;
	
	xml_document doc;
	if (GetDocument(doc)) {
		//cout << "\ngot doc";
		xpath_node xNode = doc.select_node(path.c_str());
		
		if (xNode) {
			//cout << "\ngot xnode";
			xml_node parent = xNode.parent();
			if (parent) {
				//cout << "\ngot parent";
				success = parent.remove_child(xNode.node());
				
				std::stringstream ss;
				doc.save(ss);
			
				xmlString = ss.str();
			}
		}
		
	}
	
	return success;
}

string XMLBuild::getXML() {
	return xmlString;
}

/******Private Functions *****/

bool XMLBuild::GetDocument(xml_document& returnDoc) {
	bool success = false;
	
	size_t size = strlen(xmlString.c_str());
	//cout << "\nsize: " << size;
	char* buffer = static_cast<char*>(get_memory_allocation_function()(size));
	memcpy(buffer, xmlString.c_str(), size);
	
	//cout << "\nbuffer: " << buffer;
	
	xml_parse_result result = returnDoc.load_buffer_inplace_own(buffer, size);
	
	//cout << "\n result: " << result.description();
	
	success = result;
	
	return success;
}