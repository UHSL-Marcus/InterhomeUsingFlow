/********************************************************************
// ********************** UIDeviceManager.cpp ***********************   
/************************************ Author: Marcus Lee ***********/

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
	if (params.getStringNode(M_UI_DEVICE_NAME_PATH, &name) && params.getStringNode(M_SENDER_PATH, &id)) {
		unique_lock<mutex> guard(allUIDevicesMutex);
	
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
	if (params.getStringNode(M_UI_DEVICE_ID_PATH, &id)) {

		unique_lock<mutex> guard;
		int idx = getUIDeviceIndex(id, &guard);
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
	
	unique_lock<mutex> guard;
	int idx = getUIDeviceIndex(id, &guard);
	if (idx > -1) {
		*out = allUIDevices[idx];
		return true;
	}

	return false;
}

void UIDeviceManager::uiDeviceBool(string id, bool result, string guid) {
	
	unique_lock<mutex> guard;
	int idx = getUIDeviceIndex(id, &guard);
	
	XMLBuild messageXML;
	messageXML.addStringNode(M_UI_DEVICE_BOOL, (result ? string("1") : string("0")));
	
	if (idx > -1) {
		outgoingCommandHandler.sendCommand("me", id, "UIDeviceBool", messageXML.getXML(), allUIDevices[idx].getCommunicationProtocols(), guid);
	}
}

void UIDeviceManager::uiDeviceMessage(string message, string id, string guid) {
	vector<UIDevice> recipients;
	
	unique_lock<mutex> guard(allUIDevicesMutex);
	if (id == "")
		recipients = allUIDevices; // can change to all online devices
	else {
		int idx = getUIDeviceIndex(id);
		if (idx > -1) {
			recipients.push_back(allUIDevices[idx]);
		}
	}
	
	XMLBuild messageXML;
	messageXML.addStringNode(M_UI_DEVICE_MESSAGE, message);
	
	for (int i = 0; i < recipients.size(); i++) {
		outgoingCommandHandler.sendCommand("me", recipients[i].getID(), "UIDeviceMessage", messageXML.getXML(), recipients[i].getCommunicationProtocols(), guid);
	}
}

void UIDeviceManager::uiDeviceCommand(string cmd, string data, string id, string guid) {
	vector<UIDevice> recipients;
	
	unique_lock<mutex> guard(allUIDevicesMutex);
	if (id == "")
		recipients = allUIDevices; // can change to all online devices
	else {
		int idx = getUIDeviceIndex(id);
		if (idx > -1) {
			recipients.push_back(allUIDevices[idx]);
		}
	}
	
	for (int i = 0; i < recipients.size(); i++) {
		outgoingCommandHandler.sendCommand("me", recipients[i].getID(), cmd, data, recipients[i].getCommunicationProtocols(), guid);
	}
}

/**** Private Functions ***/

int UIDeviceManager::getUIDeviceIndex(string id) {
	unique_lock<mutex> guard;
	return getUIDeviceIndex(id, &guard);
}
int UIDeviceManager::getUIDeviceIndex(string id, unique_lock<mutex> *outLock) {
	
	unique_lock<mutex> guard(allUIDevicesMutex);
	int idx = -1;
	for (int i = 0; i < allUIDevices.size(); i++) {
		string deviceID = allUIDevices[i].getID();
		if (id == deviceID && id.size() == deviceID.size()) {
			idx = i;
		}
	}
	
	*outLock = std::move(guard);
	return idx;
}

UIDeviceManager uiDeviceManager;