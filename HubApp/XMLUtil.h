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
			* @param *out 	Pointer to the string to store the text
			* @return bool 	operation success
			*/
		bool getStringNode(string path, string* out);
		
		/** Get the text within multiple XML nodes that share name and location
			*
			* @param path	Xpath query to the desired nodes
			* @param *out 	Refrence to the vector<string> to store the text
			* @return bool 	operation success
			*/
		bool getStringNodes(string path, vector<string>& out);
		
		/** Get the XML from under multiple nodes that share a name and location
			*
			* @param path	Xpath query to the desired nodes
			* @param &out 	Refrence to the vector<string> to store the XML output
			* @return bool 	operation success
			*/
		bool getNodeXML(string path, string &out);
		
		/** Get the XML from under a node
			*
			* @param path	Xpath query to the desired node
			* @param &out 	Refrence to the string to store the XML output
			* @return bool 	operation success
			*/
		bool getNodesXML(string path, vector<string> &out);
		
		/** Present the XML in the form of pairs, holding the Xpath to each text node and the text stored in the node
			*
			* @param &out	Refrence to the vector to store the pairs
			* @return bool 	operation success
			*/
		bool splitXML(vector<pair<string, string> > &out);
		
		string getSource();
		
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
		XMLBuild();
		XMLBuild(string root);
		
		/** Add a string node to the XML document
			*
			* @param path	Xpath to the node location
			* @param text 	The text to store in the node
			* @return bool 	operation success
			*/
		bool addStringNode(string path, string text);
		
		/** Add XML to the XML document
			*
			* @param path	Xpath to the node location
			* @param xml 	The XML in string form to store under the node
			* @return bool 	operation success
			*/
		bool addXML(string path, string xml);
		
		/** Remove a node from the XML document
			*
			* @param path	Xpath to the node location
			* @return bool 	operation success
			*/
		bool removeNode(string path);
		
		/** Get built XML as a string
			*
			* @return string 	The built XML
			*/
		string getXML();
	private: 
		string xmlString;
		bool GetDocument(pugi::xml_document& returnDoc);
};



#endif /* XML_UTIL_H */