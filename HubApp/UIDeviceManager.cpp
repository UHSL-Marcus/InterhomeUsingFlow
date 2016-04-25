/********************************************************************
// ********************** UIDeviceManager.cpp ***********************   
/*******************************************************************/

#include "UIDeviceManager.h"

/**** Public Functions ***/

UIDeviceManager::UIDeviceManager() {
	
}

void UIDeviceManager::setCommandCallbacks() {
	commandHandler.addCallback("AddUIDevice", UIDeviceManager::addUIDevice, this);
	commandHandler.addCallback("RemoveUIDevice", UIDeviceManager::removeUIDevice, this);
}

void UIDeviceManager::addUIDevice(ICommandCallback *parent, XMLParse params) {
	(static_cast<UIDeviceManager*>(parent))->addUIDevice(params);
}

void UIDeviceManager::addUIDevice(XMLParse params) {

	bool success = false;
	
	string name;
	string id; 
	if (params.GetStringNode(UI_DEVICE_NAME_PATH, &name) && params.GetStringNode(SENDER_PATH, &id)) {
	
		UIDevice uiDevice(id, name); 
		
		int idx = getUIDeviceIndex(id);
		if (idx < 0) {
			allUIDevices.push_back(uiDevice);
			success = true;
		}
	}
	
	// send success info to requesting device
}

void UIDeviceManager::removeUIDevice(ICommandCallback *parent, XMLParse params) {
	(static_cast<UIDeviceManager*>(parent))->removeUIDevice(params);
}

void UIDeviceManager::removeUIDevice(XMLParse params) {

	bool success = false;
	
	string id;
	if (params.GetStringNode(UI_DEVICE_ID_PATH, &id)) {

		
		int idx = getUIDeviceIndex(id);
		if (idx > -1) {
			allUIDevices.erase(allUIDevices.begin()+idx);
			
			
		}

	}
	
	// send success to requesting device
}

vector<UIDevice> UIDeviceManager::getUIDevices() {
	return allUIDevices;
}

bool UIDeviceManager::getUIDevice(string id, UIDevice *out) {
	
	int idx = getUIDeviceIndex(id);
	if (idx > -1) {
		*out = allUIDevices[idx];
		return true;
	}

	return false;
}

/**** Private Functions ***/

int UIDeviceManager::getUIDeviceIndex(string id) {
	int idx = -1;
	for (int i = 0; i < allUIDevices.size(); i++) {
		string deviceID = allUIDevices[i].getID();
		if (id == deviceID && id.size() == deviceID.size()) {
			idx = i;
		}
	}
	
	return idx;
}

UIDeviceManager uiDeviceManager;