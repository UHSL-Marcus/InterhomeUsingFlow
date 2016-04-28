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


bool XMLParse::GetStringNode(string path, string* out) {
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

XXMLBuild::XMLBuild(string root) {
	xmlString = "<" + root + "></" + root + ">";
}

bool XMLBuild::addStringNode(string path, string text) {
	bool success = false;
	
	xml_document doc;
	if (GetDocument(doc)) {
	
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
			xml_node currentNode = doc;
			for (int i = 0; i < nodeNames.size(); i++) {
				xml_node nextNode = currentNode.child(nodeNames[i]);
				if (nextNode) {
					currentNode = nextNode;
				} else {
					nextNode = currentNode.append_child(nodeNames[i]);
				}
			}
			currentNode.append_child(node_pcdata).set_value(text);
			
			std::stringstream ss;
			doc.save(ss);
			
			xmlString = ss.str();
			
			success = true;
		}
	}
	
	return success;
}

string XMLBuild::getXML(); {
	return xmlString;
} 

/******Private Functions *****/

bool XMLBuild::GetDocument(xml_document& returnDoc) {
	bool success = false;
	
	size_t size = strlen(xmlString.c_str());
	char* buffer = static_cast<char*>(get_memory_allocation_function()(size));
	memcpy(buffer, xmlString.c_str(), size);
	

	xml_parse_result result = returnDoc.load_buffer_inplace_own(buffer, size);
	
	if (result) {
		success = true;
	}
	
	return success;
}