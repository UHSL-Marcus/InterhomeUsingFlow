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
	commandHandler.addCallback("NewDevicePresence", DeviceManager::newDevicePresence, this);
	
}

vector<Device> DeviceManager::getDevices(){
	return allDevices;
}

vector<Device> DeviceManager::getPendingDevices() {
	return pendingDevices;
}

bool DeviceManager::getDevice(string id, Device *out) {
	
	int idx = getDeviceIndexID(id);
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

	string mac;
	if (params.GetStringNode(MAC_ADDR_PATH, &mac)) {
		int idx = getPendingDeviceIndex(mac);
		
		if (idx > -1 && getDeviceIndexMAC(mac) == -1) {
			
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
			
			// send update to ui device and newly addes device, informing it of it's new ID
		}
	}
	
}

void DeviceManager::newDevicePresence(ICommandCallback *parent, XMLParse params) {
	(static_cast<DeviceManager*>(parent))->newDevicePresence(params);
}
		
void DeviceManager::newDevicePresence(XMLParse params) {
	string mac; 
	if (params.GetStringNode(SENDER_PATH, &mac)) { // before being assigned an ID, a new device will use its mac address as its messaging ID.
		int idx = getDeviceIndexMAC(mac);
		
		if (idx < 0) { // make sure this mac address isn't already registered
			idx = getPendingDeviceIndex(mac);
			
			if (idx < 0) { // and not already pending

				string type;
				string primary;
				string backup;
				if (params.GetStringNode(DEVICE_TYPE_PATH, &type) && params.GetStringNode(PRIMARY_COMMS_PATH, &primary) && params.GetStringNode(BACKUP_COMMS_PATH, &backup)) {
					
					Device_Socket device(mac); // the device type will determine which device is created

					vector<string> comms;
					comms.push_back(primary);

					size_t current;
					size_t next = -1;
					do
					{
					  current = next + 1;
					  next = backup.find_first_of(',', current);
					  comms.push_back(backup.substr(current, next - current));
					}
					while (next != string::npos);
					device.setcommunicationProtocols(comms);

					
					pendingDevices.push_back(device); //the device code would use its mac address until a GUID was assinged to it
					
					// send update to UI devices, prompting user to acitvate the pending device
				
				}
			}
		}
		
	}
}

void DeviceManager::deviceHeartbeat(ICommandCallback *parent, XMLParse params) {
	(static_cast<DeviceManager*>(parent))->deviceHeartbeat(params);
}

void DeviceManager::deviceHeartbeat(XMLParse params) {

	string id;
	if (params.GetStringNode(SENDER_PATH, &id)) {
		
		int idx = getDeviceIndexID(id);
		
		if (idx > -1) {
			// do heartbeat on device
			string timestamp;
			if (params.GetStringNode(TIMESTAMP_PATH, &timestamp)) {
				allDevices[idx].doHeartbeat(timestamp);
			}
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
		
		int idx = getDeviceIndexID(id);
		if (idx > -1) {
			if (allDevices[idx].removeFromRoom()) {
				allDevices.erase(allDevices.begin()+idx);
			}
			
		}

	}
	
	// send success to requesting device
}

/**** Private Functions ***/

int DeviceManager::getDeviceIndexID(string id) {
	int idx = -1;
	for (int i = 0; i < allDevices.size(); i++) {
		string deviceID = allDevices[i].getID();
		if (id == deviceID && id.size() == deviceID.size()) {
			idx = i;
		}
	}
	
	return idx;
}

int DeviceManager::getDeviceIndexMAC(string mac) {
	int idx = -1;
	for (int i = 0; i < allDevices.size(); i++) {
		string deviceMAC = allDevices[i].getMAC();
		if (mac == deviceMAC && mac.size() == deviceMAC.size()) {
			idx = i;
		}
	}
	
	return idx;
}

int DeviceManager::getPendingDeviceIndex(string mac) {
	int idx = -1;
	for (int i = 0; i < pendingDevices.size(); i++) {
		string deviceMAC = pendingDevices[i].getMAC();
		if (mac == deviceMAC && mac.size() == deviceMAC.size()) {
			idx = i;
		}
	}
	
	return idx;
}

DeviceManager deviceManager;