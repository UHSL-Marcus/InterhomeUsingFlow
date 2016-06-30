/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "tests.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::getline;


void runTest(int i) {
	
	switch(i) {
		case 0:
			cout << "\n\n----New Room Manager Test----\n\n";
			doRoomManager_test();
			break;
		case 1:
			cout << "\n\n----New Device Test----\n\n";
			doDevice_test();
			break;
		case 2:
			cout << "\n\n----New Device Manager Test----\n\n";
			doDeviceManager_test();
			break;
		case 3:
			cout << "\n\n----New Room Device Map Manager Test----\n\n";
			doRoomDeviceMapManager_test();
			break;
		case 4:
			cout << "\n\n----New UI Device Manager Test----\n\n";
			doUIDeviceManager_test();
			break;
		case 5:
			cout << "\n\n----Command Handler Test----\n\n";
			doCommandHandler_test();
			break;
		case 6:
			cout << "\n\n----XML Builder Test----\n\n";
			doXMLBuildTest();
			break;
		case 7:
			cout << "\n\n----HTTP Request Test----\n\n";
			doHTTPRequest_test();
			break;
		case 8:
			cout << "\n\n----Thread Manager Test----\n\n";
			doThreadManager_test();
			break;
		case 9:
			cout << "\n\n----Dynamic Vector Test----\n\n";
			doDynamicVector_test();
			break;
		case 10:
			for (int t = 0; t < 9; t++) {
				runTest(t);
			}
			break;
	}
		
	doCleanup();
}


int main(void) {
	
	string info = "\n\nChoose Test:\n"
			"0: Room Manager Test\n"
			"1: Device Test\n"
			"2: Device Manager Test\n"
			"3: Room Device Map Manager Test\n"
			"4: UI Device Manager Test\n"
			"5: Command Handler Test\n"
			"6: XML Builder Test\n"
			"7: HTTP Request Test\n"
			"8: Thread Manager Test\n"
			"9: Dynamic Vector Test\n"
			"10: Run All\n";
	string command = "Enter Number (0-10, Q to quit):";
	
	
	deviceManager.setCommandCallbacks();
	roomManager.setCommandCallbacks();
	uiDeviceManager.setCommandCallbacks();
	
	//set Globals
	Global::webServiceUsr = "root";
	Global::webServicePwd = "root";
	Global::propertyID = "3";
	
	cout << info;
			
	string s;	
	while (s != "Q") {
		
		cout << command;
		
		getline(cin, s);
		stringstream ss(s);
		
		int i = -1; ss >> i;
		
		if (ss && i < 11) {
		runTest(i);
		cout << info;
		} else if (s !="Q") cout << "Out of bounds\n";
	}

	
	return 0;
}