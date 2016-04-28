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

using std::string;

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
		bool GetStringNode(string path, string* out);
	
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
		bool addStringNode(string path, string text);
		string getXML(); 
	private: 
		string xmlString;
		string 
		bool GetDocument(pugi::xml_document& returnDoc);
}



#endif /* XML_UTIL_H */