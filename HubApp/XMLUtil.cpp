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

bool nextChild(xml_node &node, vector<pair<string, string> > &out ,string path = "") {
	cout << "\n\nNext Child (" << node.name() << ")\nPath: " << path;
	bool success = false;
	xml_node_type nodeType = node.type();
	
	if (nodeType == node_document || nodeType == node_element) {
		cout << "\nDoc or Element";
		xml_node child = node.first_child();
		
		if (nodeType == node_element)
				path += string(node.name()) + string("/");
		
		if (child.type() == node_pcdata) {
			cout << "\nText element\nPath: " << path.substr(0, path.size()-2) << ", text: " << child.value();
			out.push_back(std::make_pair(path.substr(0, path.size()-2) ,string(child.value())));
			cout << "\nvector count: " << out.size();
			success = true;
		} else {
		
			cout << "\nnew path: " << path;
			
			while (child) {
				cout << "\nanother child";
				
				nextChild(child, out, path);

				child = node.next_sibling();
				
				if (out.size() > 10) break;
			}
		}
		
	}
	return success;
} 
bool XMLParse::splitXML(vector<pair<string, string> > &out) {
	bool success = false;
	
	xml_document doc;
	if (GetDocument(doc)) {
		success = nextChild(doc, out);
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
	this->root = root;
}

bool XMLBuild::addStringNode(string path, string text) {
	
	//cout << "\n\nAdding string node. Path: " << path << ", text: " << text;
	bool success = false;
	
	xml_node rootNode;
	xml_document doc;
	if (GetDocumentRoot(rootNode, doc)) {
		//cout << "\nroot name: " << rootNode.name();
		
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
		
		if (nodeNames.size() > 0) {
			//cout << "\nsplit node names";
			xml_node currentNode = rootNode;
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
	bool success = false;
	
	xml_node rootNode;
	xml_document doc;
	if (GetDocumentRoot(rootNode, doc)) {
		//cout << "\nroot name: " << rootNode.name();
		
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
		
		if (nodeNames.size() > 0) {
			//cout << "\nsplit node names";
			xml_node currentNode = rootNode;
			for (int i = 0; i < nodeNames.size(); i++) {
				//cout << "\ncurrent node name: " << currentNode.name();
				xml_node nextNode = currentNode.child(nodeNames[i].c_str());
				if (!nextNode) {
					//cout << "\ncreating nextNode (" << nodeNames[i] << ")";
					nextNode = currentNode.append_child(nodeNames[i].c_str());
				}
				currentNode = nextNode;
			}
			
		}
	}
}

string XMLBuild::getXML() {
	return xmlString;
}

/******Private Functions *****/

bool XMLBuild::GetDocumentRoot(pugi::xml_node& rootNode, xml_document& returnDoc) {
	bool success = false;
	
	size_t size = strlen(xmlString.c_str());
	char* buffer = static_cast<char*>(get_memory_allocation_function()(size));
	memcpy(buffer, xmlString.c_str(), size);
	
	
	xml_parse_result result = returnDoc.load_buffer_inplace_own(buffer, size);
	
	if (result) {
		rootNode = returnDoc.child(root.c_str());
		success = true;
	}
	
	return success;
}