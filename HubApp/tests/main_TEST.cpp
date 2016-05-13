/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "tests.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;


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
	}
		
	doCleanup();
}


int main(void) {
	
	deviceManager.setCommandCallbacks();
	roomManager.setCommandCallbacks();
	uiDeviceManager.setCommandCallbacks();
	
	
	
	cout << "\nChoose Test:\n"
			"0: Room Manager Test\n"
			"1: Device Test\n"
			"2: Device Manager Test\n"
			"3: Room Device Map Manager Test\n"
			"4: UI Device Manager Test\n"
			"5: Command Handler Test\n"
			"6: XML Builder Test\n"
			"7: HTTP Request Test\n"
			"8: Run All";
	int i;
	
	while (i != 9) {
		i = -1;
		cout << "\nEnter Number (0-8, 9 to quit):";
		cin >> i;
		
		if (i > -1 && i < 8) 
			runTest(i);
		else if (i == 8) {
			for (int t = 0; t < 8; t++) {
				runTest(t);
			}
		} else if (i != 9) cout << "Out of bounds\n";
		
	}

	
	return 0;
}