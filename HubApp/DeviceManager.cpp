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
	commandHandler.addCallback("DeviceCommand", DeviceManager::deviceCommand, this);
	commandHandler.addCallback("DeviceStateChanged", DeviceManager::deviceStateChange, this);
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
	
	bool success = false;

	string mac;
	if (params.getStringNode(M_DEVICE_MAC_PATH, &mac)) {
		int idx = getPendingDeviceIndex(mac);
		
		if (idx > -1 && getDeviceIndexMAC(mac) == -1) {
			
			// generate GUID for device and add it to it along with any extra info the user sent
			string roomID;
			string name; 
			if (params.getStringNode(M_ROOM_ID_PATH, &roomID) && params.getStringNode(M_DEVICE_NAME_PATH, &name)) {

				Device device = pendingDevices[idx];
				string id = name;
				device.setID(id); // generate GUID for device and add it to it along with any extra info the user sent
				device.setRoom(roomID);
				device.setName(name);
				
				
				allDevices.push_back(device);
				pendingDevices.erase(pendingDevices.begin()+idx);
				
				// send update to newly addes device, informing it of it's new ID
				XMLBuild messageXML;
				messageXML.addStringNode(M_DEVICE_ID, id);
				
				outgoingCommandHandler.sendCommand("me", id, "DeviceSettingsUpdate", messageXML.getXML(), device.getCommunicationProtocols());
				
				success = true;
			}
			
			
			
		}
	}
	
	// send success to UI device 
	string uiID;
	string guid;
	if (params.getStringNode(M_SENDER_PATH, &uiID) && params.getStringNode(M_GUID_PATH, &guid)) 	
		uiDeviceManager.uiDeviceBool(uiID, success, guid);
	
	
}

void DeviceManager::newDevicePresence(ICommandCallback *parent, XMLParse params) {
	(static_cast<DeviceManager*>(parent))->newDevicePresence(params);
}
		
void DeviceManager::newDevicePresence(XMLParse params) {
	string mac; 
	if (params.getStringNode(M_SENDER_PATH, &mac)) { // before being assigned an ID, a new device will use its mac address as its messaging ID.
		int idx = getDeviceIndexMAC(mac);
		
		if (idx < 0) { // make sure this mac address isn't already registered
			idx = getPendingDeviceIndex(mac);
			
			if (idx < 0) { // and not already pending

				string type;
				string primary;
				string backup;
				if (params.getStringNode(M_DEVICE_TYPE_PATH, &type) && params.getStringNode(M_PRIMARY_COMMS_PATH, &primary) && params.getStringNode(M_BACKUP_COMMS_PATH, &backup)) {
					
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
					device.setCommunicationProtocols(comms);

					
					pendingDevices.push_back(device); //the device code would use its mac address until a GUID was assinged to it
					
					// send update to UI devices, prompting user to activate the pending device
					XMLBuild messageXML;
					messageXML.addStringNode(M_DEVICE_TYPE, type);
					messageXML.addStringNode(M_DEVICE_MAC, mac);
					
					uiDeviceManager.uiDeviceCommand("NewDevicePresence", messageXML.getXML());
					
				
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
	if (params.getStringNode(M_SENDER_PATH, &id)) {
		
		int idx = getDeviceIndexID(id);
		
		if (idx > -1) {
			// do heartbeat on device
			string timestamp;
			if (params.getStringNode(M_TIMESTAMP_PATH, &timestamp)) {
				allDevices[idx].doHeartbeat(timestamp);
			}
		} 
			
		
			
	}
}

void DeviceManager::deviceCommand(ICommandCallback *parent, XMLParse params){
	(static_cast<DeviceManager*>(parent))->deviceCommand(params);	
}
		
void DeviceManager::deviceCommand(XMLParse params) {
	bool offloaded = false;
	
	string id;
	string cmd;
	if (params.getStringNode(M_DEVICE_ID_PATH, &id) && params.getStringNode(M_DEVICE_CMD_PATH, &cmd)) {
		int idx = getDeviceIndexID(id);
		
		if (idx > -1) {
			string data;
			if (!params.getNodeXML(M_DEVICE_CMD_DATA_PATH, data))
				data = "";
			
			
			outgoingCommandHandler.sendCommand("me", id, cmd, data, allDevices[idx].getCommunicationProtocols());
			
			offloaded = true;
			
			// if send fails callback function will be informed
		}
		
	}
	
	if (!offloaded) {
		// send success to UI device 
		string uiID;
		string guid;
		if (params.getStringNode(M_SENDER_PATH, &uiID) && params.getStringNode(M_GUID_PATH, &guid)) 	
			uiDeviceManager.uiDeviceBool(uiID, false, guid);
	}
}

void DeviceManager::deviceStateChange(ICommandCallback *parent, XMLParse params) {
	(static_cast<DeviceManager*>(parent))->deviceStateChange(params);	
}
		
void DeviceManager::deviceStateChange(XMLParse params) {
	
	bool success = false;
	
	string id;
	if (params.getStringNode(M_SENDER_PATH, &id)) {
		
		int idx = getDeviceIndexID(id);
		
		
		if (idx > -1) {
			
			vector<string> statePairs;
			if (params.getNodesXML(M_DEVICE_STATE_PAIR_PATH, statePairs)) {
				for (int i = 0; i < statePairs.size(); i++) {
					XMLParse statePair(statePairs[i]);
					
					string stateName;
					string stateValue;
					if (statePair.getStringNode(M_DEVICE_STATE_NAME, &stateName) && statePair.getStringNode(M_DEVICE_STATE_VALUE, &stateValue)) {
						if (allDevices[idx].changeStateValue(stateName, stateValue)) {
							success = true;
						} else {// possibly return error to the device, possible to put error correction code in them.}
					}
				}
			}
		} 
	}

	if (success) {
		// send state update for this device to all online UI devices
	}
}

void DeviceManager::removeDevice(ICommandCallback *parent, XMLParse params) {
	(static_cast<DeviceManager*>(parent))->removeDevice(params);	
}

void DeviceManager::removeDevice(XMLParse params) {
	bool success = false;
	
	string id;
	if (params.getStringNode(M_DEVICE_ID_PATH, &id)) {
		
		int idx = getDeviceIndexID(id);
		if (idx > -1) {
			if (allDevices[idx].removeFromRoom()) {
				allDevices.erase(allDevices.begin()+idx);
				success = true;
				// send new device configuration to UI
			}
			
		}

	}
	
	// send success to UI device 
	string uiID;
	string guid;
	if (params.getStringNode(M_SENDER_PATH, &uiID) && params.getStringNode(M_GUID_PATH, &guid)) 	
		uiDeviceManager.uiDeviceBool(uiID, success, guid);
	
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