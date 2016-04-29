/********************************************************************
// **************************** XMLUtil.h ***************************
/*******************************************************************/

#ifndef XML_UTIL_H
#define XML_UTIL_H

#include "pugiXML/pugixml.hpp"
#include "MessageFormat.h"
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <utility>

using std::string;
using std::vector;
using std::pair;

class XMLParse {
	public:
		/** Constructor
			*
			* @param _source	The source XML to parse
			*/
		XMLParse(string _source);
		
		/** Get the text within an XML node
			*
			* @param path	Xpath query to the desired node
			* @param out 	Pointer to the string to store the text
			* @return bool 	operation success
			*/
		bool getStringNode(string path, string* out);
		
		bool splitXML(vector<pair<string, string> > &out);
	
	private:
		string source;
		bool GetDocument(pugi::xml_document& returnDoc);
};

class XMLBuild {
	public:
		/** Constructor
			*
			* @param root	The name of the root node
			*/
		XMLBuild(string root);
		
		/** Add a string node to the XML document
			*
			* @param path	Xpath to the node location
			* @param text 	The text to store in the node
			* @return bool 	operation success
			*/
		bool addStringNode(string path, string text);
		
		bool addXML(string path, string xml);
		
		/** Get built XML as a string
			*
			* @return string 	The built XML
			*/
		string getXML();
	private: 
		string xmlString;
		string root;
		bool GetDocumentRoot(pugi::xml_node& rootNode, pugi::xml_document& returnDoc);
};



#endif /* XML_UTIL_H */