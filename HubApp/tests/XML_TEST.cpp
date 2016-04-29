


#include "XML_TEST.h"

namespace XML_TEST {
	
	void singleAddTest(XMLBuild &xmlBuild, string path, string text) {
		
		xmlBuild.addStringNode(path, text);
		cout << "\n\nAdded " << path << ", text: " << text;
		cout << "\nXML: " << xmlBuild.getXML();
		
		XMLParse xmlParse(xmlBuild.getXML());
		string outText;
		cout << "\nParsing '"<< path << "' : ";
		if (xmlParse.getStringNode("testRoot/" + path, &outText)) {
			cout << outText;
		} else {cout << "parse failed";}
	}
}
using namespace XML_TEST;

void doXMLBuildTest() {
	
	XMLBuild xmlBuild("testRoot");
	cout << "inialised XML with root node: testRoot";
	cout << "\nXML: " << xmlBuild.getXML();
	
	singleAddTest(xmlBuild, "level1/text1", "text1text");
	
	singleAddTest(xmlBuild, "level1/level2/text2", "text2text");
	
	singleAddTest(xmlBuild, "level1/level2/text3", "text3text");
	
	singleAddTest(xmlBuild, "level1/text4", "text4text");
	
	singleAddTest(xmlBuild, "level1/xml1", "<XML1><XML2>XML</XML2></XML1>");
	
	XMLParse xmlParse(xmlBuild.getXML());
	vector<pair<string, string> > xmlVector;
	xmlParse.splitXML(xmlVector);
	
	cout << "\n\nExtract XML info";
	for (int i = 0; i < xmlVector.size(); i++) {
		cout << "\nPath: " << xmlVector[i].first << ", text: " << xmlVector[i].second;
	}
	
	
}