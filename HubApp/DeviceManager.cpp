/********************************************************************
// *********************** DeviceManager.cpp ************************   
/************************************ Author: Marcus Lee ***********/

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
	unique_lock<MutexCheckable> guard(allDevicesMutex);
	return allDevices;
}

vector<Device> DeviceManager::getPendingDevices() {
	unique_lock<MutexCheckable> guard(pendingDevicesMutex);
	return pendingDevices;
}

bool DeviceManager::getDevice(string id, Device *out) {
	
	unique_lock<MutexCheckable> guard;
	int idx = getDeviceIndexID(id, &guard);
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
		
		unique_lock<MutexCheckable> pendingGuard;
		unique_lock<MutexCheckable> guard(allDevicesMutex, std::defer_lock);
		int idx = getPendingDeviceIndex(mac, &pendingGuard, guard);
		
		if (idx > -1 && getDeviceIndexMAC(mac) == -1) {
			
			string roomID;
			string name; 
			if (params.getStringNode(M_ROOM_ID_PATH, &roomID) && params.getStringNode(M_DEVICE_NAME_PATH, &name)) {
				
				Device device = pendingDevices[idx];
				
				// Add new device to the database and get the ID back
				XMLBuild body("SetNewDevice");
				body.addAttribute("SetNewDevice", "xmlns", "http://tempuri.org/");
				body.addAttribute("SetNewDevice/device", "xmlns:b", "http://schemas.datacontract.org/2004/07/SmartSocketsWebService");
				body.addAttribute("SetNewDevice/device", "xmlns:i", "http://www.w3.org/2001/XMLSchema-instance");
				body.addAttribute("SetNewDevice/device/b:Commands", "xmlns:c", "http://schemas.microsoft.com/2003/10/Serialization/Arrays");

				body.addStringNode("SetNewDevice/device/b:DeviceName", name);
				body.addIntNode("SetNewDevice/device/b:DeviceTypeID", device.getTypeID());
				body.addStringNode("SetNewDevice/device/b:RoomID", roomID);
				body.addStringNode("SetNewDevice/device/b:Commands/c:string", "temp", false);
				body.addStringNode("SetNewDevice/device/b:Commands/c:string", "temp2", false);
				
				
				HTTPRequest req;
				string response;
				req.SOAPRequest(body.getXML(), "SetNewDevice", response);
				
				XMLParse reply(response);
				
				string requestOutcome;
				if (reply.getStringNode("//SetNewDeviceResult", &requestOutcome)) {
					if (requestOutcome.compare("true") == 0) {
						
						string id;
						if (reply.getStringNode("//ID", &id)) {
							
							try {
								std::stoi(id, NULL, 10); // just testing the ID to make sure it is an int
								
								
								device.setID(id);
								device.setRoom(roomID);
								device.setName(name);
								
								
								allDevices.push_back(device);
								pendingDevices.erase(pendingDevices.begin()+idx);
								
								// send update to newly addes device, informing it of it's new ID
								XMLBuild messageXML;
								messageXML.addStringNode(M_DEVICE_ID, id);
								
								outgoingCommandHandler.sendCommand("me", mac, "DeviceSettingsUpdate", messageXML.getXML(), device.getCommunicationProtocols());
								
								success = true;
								
							}
							catch (exception& e) {
								
							}
							
						}
					}
				}

				
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
		
		unique_lock<MutexCheckable> guard;
		int idx = getDeviceIndexMAC(mac, &guard);
		
		if (idx < 0) { // make sure this mac address isn't already registered
			guard.unlock();
			
			unique_lock<MutexCheckable> pendingGuard;
			idx = getPendingDeviceIndex(mac, &pendingGuard);
			
			if (idx < 0) { // and not already pending

				string typeID;
				string primary;
				string backup;
				if (params.getStringNode(M_DEVICE_TYPE_ID_PATH, &typeID) && params.getStringNode(M_PRIMARY_COMMS_PATH, &primary) && params.getStringNode(M_BACKUP_COMMS_PATH, &backup)) {
					
					try 
					{
						Device *device;
						switch (std::stoi(typeID, NULL, 10)) // the device types will be hard-coded, when new types are added, software will be updated to support them.
						{
							case 1: device = new Device_Socket(mac);
						}
						 // the device type will determine which device is created

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
						device->setCommunicationProtocols(comms);

						
						pendingDevices.push_back(*device); //the device code would use its mac address until a GUID was assinged to it
						
						delete device;
						
						// send update to UI devices, prompting user to activate the pending device
						XMLBuild messageXML;
						messageXML.addStringNode(M_DEVICE_TYPE_ID, typeID);
						messageXML.addStringNode(M_DEVICE_MAC, mac);
						
						uiDeviceManager.uiDeviceCommand("NewDevicePresence", messageXML.getXML());
					}
					catch (exception& e) {
						
					}
					
				
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
		
		unique_lock<MutexCheckable> guard;
		int idx = getDeviceIndexID(id, &guard);
		
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
		
		unique_lock<MutexCheckable> guard;
		int idx = getDeviceIndexID(id, &guard);
		
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
		
		unique_lock<MutexCheckable> guard;
		int idx = getDeviceIndexID(id, &guard);
		
		
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
						} else {
							// possibly return error to the device, possible to put error correction code in them.
						}
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
		
		unique_lock<MutexCheckable> guard;
		int idx = getDeviceIndexID(id, &guard);
		if (idx > -1) {
			
			XMLBuild body("RemoveDevice");
			body.addAttribute("RemoveDevice", "xmlns", "http://tempuri.org/");
			body.addStringNode("RemoveDevice/ID", id);
			
			HTTPRequest req;
			string response;
			req.SOAPRequest(body.getXML(), "RemoveDevice", response);
			
			XMLParse reply(response);
			
			string requestOutcome;
			if (reply.getStringNode("//RemoveDeviceResult", &requestOutcome)) {
				if (requestOutcome.compare("true") == 0) {
					if (allDevices[idx].removeFromRoom()) {
						allDevices.erase(allDevices.begin()+idx);
						success = true;
						// send new device configuration to UI
					}
				}
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

int DeviceManager::getPendingDeviceIndex(string mac) {
	unique_lock<MutexCheckable> guard;
	return getPendingDeviceIndex(mac, &guard);
}
int DeviceManager::getPendingDeviceIndex(string mac, unique_lock<MutexCheckable> *outLock) {
	if (!pendingDevicesMutex.is_locked())
		*outLock = unique_lock<MutexCheckable>(pendingDevicesMutex);
	
	int idx = -1;
	for (int i = 0; i < pendingDevices.size(); i++) {
		string deviceMAC = pendingDevices[i].getMAC();
		if (mac == deviceMAC && mac.size() == deviceMAC.size()) {
			idx = i;
		}
	}
	
	return idx;
}

int DeviceManager::getDeviceIndexID(string id) {
	unique_lock<MutexCheckable> guard;
	return getDeviceIndexID(id, &guard);	
}
int DeviceManager::getDeviceIndexID(string id, unique_lock<MutexCheckable> *outLock) {
	
	if (!allDevicesMutex.is_locked())
		*outLock = unique_lock<MutexCheckable>(allDevicesMutex);
	
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
	unique_lock<MutexCheckable> guard;
	return getDeviceIndexMAC(mac, &guard);	
}
int DeviceManager::getDeviceIndexMAC(string mac, unique_lock<MutexCheckable> *outLock) {
	
	if (!allDevicesMutex.is_locked())
		*outLock = unique_lock<MutexCheckable>(allDevicesMutex);
	
	int idx = -1;
	for (int i = 0; i < allDevices.size(); i++) {
		string deviceMAC = allDevices[i].getMAC();
		if (mac == deviceMAC && mac.size() == deviceMAC.size()) {
			idx = i;
			
		}
	}
	
	return idx;
}


DeviceManager deviceManager;