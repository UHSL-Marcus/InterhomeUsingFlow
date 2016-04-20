/********************************************************************
// *********************** DeviceManager.cpp ************************   
/*******************************************************************/

#include "DeviceManager.h"

DeviceManager::DeviceManager() {
	commandHandler.addCallback("AddPendingDevice", DeviceManager::addPendingDevice, this);
	commandHandler.addCallback("RemoveDevice", DeviceManager::removeDevice, this);
	commandHandler.addCallback("DeviceHeartbeat", DeviceManager::deviceHeartbeat, this);
}

vector<Device> DeviceManager::getDevices(){
	return allDevices;
}

Device* DeviceManager::getDevice(string id) {
	Device* device = NULL;
	
	int idx = getDeviceIndex(id);
	if (idx > -1)
		device = &allDevices[idx];

	return device;
}

void DeviceManager::addPendingDevice(ICommandCallback *parent, XMLParse params){
	(static_cast<DeviceManager*>(parent))->addPendingDevice(params);
}

void DeviceManager::addPendingDevice(XMLParse params) {
	
	string id;
	if (params.GetStringNode(TEMP_ID_PATH, &id)) {
		int idx = getPendingDeviceIndex(id);
		
		if (idx > -1 && getDeviceIndex(id) == -1) {
			
			Device device = pendingDevices[idx];
			// generate GUID for device and add it to it along with any extra info the user sent
			
			allDevices.push_back(device);
			pendingDevices.erase(pendingDevices.begin()+idx);
			
			// send update to ui device
		}
	}
	
}

void DeviceManager::deviceHeartbeat(ICommandCallback *parent, XMLParse params) {
	(static_cast<DeviceManager*>(parent))->deviceHeartbeat(params);
}

void DeviceManager::deviceHeartbeat(XMLParse params) {
	
	string id;
	if (params.GetStringNode(SENDER_PATH, &id)) {
		int idx = getDeviceIndex(id);
		if (idx > -1) {
			// do heartbeat on device
		} else {
			idx = getPendingDeviceIndex(id);
			
			if (idx > -1) {
				Device device(id); //the device code would use its mac address until a GUID was assinged to it
				
				pendingDevices.push_back(device);
				
				// send update to UI devices, prompting user to acitvate the pending device
			}
			
			// possibly put in a function for reminders to add device
			
		}
			
	}
}

void DeviceManager::removeDevice(ICommandCallback *parent, XMLParse params) {
	(static_cast<DeviceManager*>(parent))->removeDevice(params);	
}

void DeviceManager::removeDevice(XMLParse params) {
	bool success = false;
	
	string id;
	if (params.GetStringNode(ROOM_ID_PATH, &id)) {
		
		int idx = getDeviceIndex(id);
		if (idx > -1) 
			allDevices.erase(allDevices.begin()+idx);

	}
	
	// send success to requesting device
}

int DeviceManagerManager::getDeviceIndex(string id) {
	int idx = -1;
	for (int i = 0; i < allDevices.size(); i++) {
		string deviceID = allDevices[i].getID();
		if (id == deviceID && id.size() == deviceID.size()) {
			idx = i;
		}
	}
	
	return idx;
}

int DeviceManagerManager::getPendingDeviceIndex(string id) {
	int idx = -1;
	for (int i = 0; i < pendingDevices.size(); i++) {
		string deviceID = pendingDevices[i].getID();
		if (id == deviceID && id.size() == deviceID.size()) {
			idx = i;
		}
	}
	
	return idx;
}

DeviceManager deviceManager;