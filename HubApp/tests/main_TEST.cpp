/********************************************************************
// **************************** main.cpp ****************************
/*******************************************************************/

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
				cout << "\n\n----New Device Manager Test----\n\n";
				doDeviceManager_test();
				break;
			case 2:
				cout << "\n\n----New Room Device Map Manager Test----\n\n";
				doRoomDeviceMapManager_test();
				break;
			case 3:
				cout << "\n\n----New UI Device Manager Test----\n\n";
				doUIDeviceManager_test();
				break;
			case 4:
				cout << "\n\n----Command Handler Test----\n\n";
				doCommandHandler_test();
				break;
		}
}


int main(void) {
	
	cout << "Choose Test:\n0: Room Manager Test\n1: Device Manager Test\n2: Room Device Map Manager Test\n3: UI Device Manager Test\n4: Command Handler Test\n5: Run All";
	int i;
	
	while (i != 9) {
		i = -1;
		cout << "Enter Number (0-4, 9 to quit):";
		cin >> i;
		
		if (i > -1 && i < 5) 
			runTest(i);
		else if (i == 5) {
			for (int t = 0; t < 5; t++) {
				runTest(t);
			}
		} else if (i != 9) cout << "Out of bounds\n";
		
	}

	
	return 0;
}