/********************************************************************
// *********************** DeviceManager.cpp ************************   
/*******************************************************************/

#include "DeviceManager.h"

/**** Public Functions ***/

DeviceManager::DeviceManager() {
	
}

void DeviceManager::setCommandCallbacks() {
	commandHandler.addCallback("AddPendingDevice", DeviceManager::addPendingDevice, this);
	commandHandler.addCallback("RemoveDevice", DeviceManager::removeDevice, this);
	commandHandler.addCallback("DeviceHeartbeat", DeviceManager::deviceHeartbeat, this);
}

vector<Device> DeviceManager::getDevices(){
	return allDevices;
}

vector<Device> DeviceManager::getPendingDevices() {
	return pendingDevices;
}

bool DeviceManager::getDevice(string id, Device *out) {
	
	int idx = getDeviceIndex(id);
	if (idx > -1) {
		*out = allDevices[idx];
		return true;
	}

	return false;
}

void DeviceManager::addPendingDevice(ICommandCallback *parent, XMLParse params){
	(static_cast<DeviceManager*>(parent))->addPendingDevice(params);
}

void DeviceManager::addPendingDevice(XMLParse params) {

	string id;
	if (params.GetStringNode(TEMP_ID_PATH, &id)) {

		int idx = getPendingDeviceIndex(id);
		

		if (idx > -1 && getDeviceIndex(id) == -1) {
			
			// generate GUID for device and add it to it along with any extra info the user sent
			string roomID;
			string name; 
			if (params.GetStringNode(ROOM_ID_PATH, &roomID) && params.GetStringNode(DEVICE_NAME_PATH, &name)) {
				
				Device device = pendingDevices[idx];
				device.setID(name); // generate GUID for device and add it to it along with any extra info the user sent
				device.setRoom(roomID);
				device.setName(name);
				
				
				allDevices.push_back(device);
				pendingDevices.erase(pendingDevices.begin()+idx);
			}
			
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
			
			if (idx < 0) {
				string type;
				if (params.GetStringNode(DEVICE_TYPE_PATH, &type)) {
					
					
					Device_Socket device(id);
					pendingDevices.push_back(device); //the device code would use its mac address until a GUID was assinged to it
					
					// send update to UI devices, prompting user to acitvate the pending device
				}
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
	if (params.GetStringNode(DEVICE_ID_PATH, &id)) {
		
		int idx = getDeviceIndex(id);
		if (idx > -1) {
			if (allDevices[idx].removeFromRoom()) {
				allDevices.erase(allDevices.begin()+idx);
			}
			
		}

	}
	
	// send success to requesting device
}

/**** Private Functions ***/

int DeviceManager::getDeviceIndex(string id) {
	int idx = -1;
	for (int i = 0; i < allDevices.size(); i++) {
		string deviceID = allDevices[i].getID();
		if (id == deviceID && id.size() == deviceID.size()) {
			idx = i;
		}
	}
	
	return idx;
}

int DeviceManager::getPendingDeviceIndex(string id) {
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