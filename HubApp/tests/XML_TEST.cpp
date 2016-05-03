


#include "XML_TEST.h"

namespace XML_TEST {
	
	void singleAddTest(XMLBuild &xmlBuild, string path, string text) {
		
		xmlBuild.addStringNode(path, text);
		cout << "\n\nAdded " << path << ", text: " << text;
		cout << "\nXML: " << xmlBuild.getXML();
		
		XMLParse xmlParse(xmlBuild.getXML());
		string outText;
		cout << "\nParsing '"<< path << "' : ";
		if (xmlParse.getStringNode(path, &outText)) {
			cout << outText;
		} else {cout << "parse failed";}
	}
	
	void singleAddXMLTest(XMLBuild &xmlBuild, string path, string xml) {
		xmlBuild.addXML(path, xml);
		cout << "\n\nAdded " << path << ", XML: " << xml;
		cout << "\nXML: " << xmlBuild.getXML();
		
		XMLParse xmlParse(xmlBuild.getXML());
		string outText;
		cout << "\nParsing '"<< path << "' : ";
		if (xmlParse.getNodeXML(path, outText)) {
			cout << outText;
		} else {cout << "parse failed";}
	}
	
	void singleRemoveTest(XMLBuild &xmlBuild, string path) {
		xmlBuild.removeNode(path);
		
		cout << "\n\nRemoved " << path;
		cout << "\nXML: " << xmlBuild.getXML();
		
		XMLParse xmlParse(xmlBuild.getXML());
		string outText;
		cout << "\nParsing '"<< path << "' : ";
		if (xmlParse.getStringNode(path, &outText)) {
			cout << "Not Removed";
		} else {cout << "Removed";}
	}
}
using namespace XML_TEST;

void doXMLBuildTest() {
	
	XMLBuild xmlBuild("testRoot");
	cout << "\ninialised XML with root node: testRoot";
	cout << "\nXML: " << xmlBuild.getXML();
	
	singleAddTest(xmlBuild, "testRoot/level1/text1", "text1text");
	
	singleAddTest(xmlBuild, "testRoot/level1/level2/text2", "text2text");
	
	singleAddTest(xmlBuild, "testRoot/level1/level2/text3", "text3text");
	
	singleRemoveTest(xmlBuild, "testRoot/level1/level2/text3");
	
	singleAddTest(xmlBuild, "testRoot/level1/text4", "text4text");
	
	XMLBuild xmlBuild2;
	cout << "\ninialised XML with no root node";
	singleAddTest(xmlBuild2, "XML1/XML2", "XML");
	singleAddTest(xmlBuild2, "XML3/XML4", "XML2");
	
	singleAddXMLTest(xmlBuild, "testRoot/level1/xml1", xmlBuild2.getXML());
	
	cout << "\n\nExtracting XML to XPath";
	XMLParse xmlParse(xmlBuild.getXML());
	vector<pair<string, string> > xmlVector;
	if (xmlParse.splitXML(xmlVector)){
	
		cout << "\n\nExtracted XML info";
		for (int i = 0; i < xmlVector.size(); i++) {
			cout << "\nPath: " << xmlVector[i].first << ", text: " << xmlVector[i].second;
		}
	} else cout << "\nExtract failed";
	
	
}