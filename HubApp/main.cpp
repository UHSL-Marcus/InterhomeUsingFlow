/********************************************************************
// **************************** main.cpp ****************************
/*******************************************************************/

#include "main.h"
#include <iostream>

int main(void) {
	
	while (1) {
		
		
		
		std::cout << "Type ID\n";
		char* i = new char[5];
		std::cin >> i;
		std::cout << "ID: " << i << "\n";
		commandHandler.handleCmd("AddNewRoom");
		
	}
	return 0;
}