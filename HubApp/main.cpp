/********************************************************************
// **************************** main.cpp ****************************
/*******************************************************************/

#include "main.h"
#include "XMLUtil.h"
#include <iostream>

int main(void) {
	
	std::cout << "press any btn\n";
	char k;
	std::cin >> k;
	while (k != (char) 0) {
		
		char* xml = "<packet><data><name>test</name></data></packet>";
		XMLParse xmlP(xml);
		
		commandHandler.handleCmd("AddNewRoom", xmlP);
		
		std::cout << "press any btn\n";
		std::cin >> k;
		
	}
	return 0;
}