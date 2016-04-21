/********************************************************************
// *************************** XMLUtil.cpp **************************
/*******************************************************************/

#include "XMLUtil.h"

using namespace pugi;

XMLParse::XMLParse(string _source) {
	
	source = _source;
}

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

bool XMLParse::GetStringNode(string path, string* out) {
	
	bool success = false;
	string text;
	
	xml_document doc;
	if (GetDocument(doc)) {
	
		xpath_node node = doc.select_node(path.c_str());
		
		if (node) {
			text = node.node().child_value();
			if (text.size() > 0) {
				*out = string(text);
				success = true;
			}
		}
	}
	
	return success;
	
}