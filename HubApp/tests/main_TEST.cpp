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
	}
		
	doCleanup();
}


int main(void) {
	
	deviceManager.setCommandCallbacks();
	roomManager.setCommandCallbacks();
	uiDeviceManager.setCommandCallbacks();
	
	
	
	cout << "Choose Test:\n0: Room Manager Test\n1: Device Test\n2: Device Manager Test\n3: Room Device Map Manager Test\n4: UI Device Manager Test\n5: Command Handler Test\n6: XML Builder Test\n7: Run All";
	int i;
	
	while (i != 9) {
		i = -1;
		cout << "\nEnter Number (0-7, 9 to quit):";
		cin >> i;
		
		if (i > -1 && i < 7) 
			runTest(i);
		else if (i == 7) {
			for (int t = 0; t < 7; t++) {
				runTest(t);
			}
		} else if (i != 9) cout << "Out of bounds\n";
		
	}

	
	return 0;
}