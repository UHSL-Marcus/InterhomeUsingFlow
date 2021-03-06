/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "UIDeviceManager_TEST.h"

namespace UIDeviceManager_TEST {
	bool addedCommands = false;
	
	void printUIDevices() {
		
		vector<UIDevice> uidevices = uiDeviceManager.getUIDevices();
		
		cout << "\nUI Devices: ";
		for (int i = 0; i < uidevices.size(); i++) {
			cout << uidevices[i].getID() + "(" + uidevices[i].getName() + ") ";
		}
		
		cout << "\n";
	}
}

using namespace UIDeviceManager_TEST;


void doUIDeviceManager_test() {
	
	if(!addedCommands) {
		uiDeviceManager.setCommandCallbacks();
		addedCommands = true;
	}
	
	XMLParse add1("<packet><from>uidevice1</from><data><ui_device_name>ui device 1 name</ui_device_name></data></packet>");
	XMLParse add2("<packet><from>uidevice2</from><data><ui_device_name>ui device 2 name</ui_device_name></data></packet>");
	
	XMLParse remove("<packet><data><ui_device_id>uidevice1</ui_device_id></data></packet>");
	
	commandHandler.handleCmd("AddUIDevice", add1);
	commandHandler.handleCmd("AddUIDevice", add2);
	
	threadManager.joinAllThreads();
	cout << "added ui devices\n";
	printUIDevices();
	
	commandHandler.handleCmd("RemoveUIDevice", remove);
	
	threadManager.joinAllThreads();
	cout << "removed UI device 1\n";
	printUIDevices();
	
}