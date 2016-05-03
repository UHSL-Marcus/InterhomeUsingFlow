/********************************************************************
// *************************** Device.cpp ***************************          
/*******************************************************************/


#include "Device.h"

/**** Public Functions ***/


Device::Device(string mac, string type, string stateList) : deviceMAC(mac), deviceType(type) {
	
	string allStates = GENERAL_STATE_LIST + string(",") + stateList;
	size_t current;
	size_t next = -1;
	do
	{
	  current = next + 1;
	  next = allStates.find_first_of(',', current);
	  state.insert(std::pair<string,string>(allStates.substr(current, next - current),""));
	}
	while (next != string::npos);
	
}

void Device::setID(string id) {
	deviceID = id;
}

void Device::setMAC(string mac) {
	deviceMAC = mac;
}

void Device::setName(string name) {
	deviceName = name;
}

void Device::setRoom(string room_id) {
	roomDeviceMapManager.addDevice(room_id, deviceID);
}

string Device::getID() {
	return deviceID;
}

string Device::getMAC() {
	return deviceMAC;
}

string Device::getName() {
	return deviceName;
}

string Device::getRoom() {
	string room = "";
	roomDeviceMapManager.getDeviceRoom(deviceID, &room);
	
	return room;
}

bool Device::removeFromRoom() { // put this is the destruction method?
	return roomDeviceMapManager.removeDevice(deviceID);
}

string Device::getType() {
	return deviceType;
}
		
vector<string> Device::getStateFieldNames(){
	vector<string> names;
	
	for (map<string,string>::iterator itr=state.begin(); itr!=state.end(); ++itr) {
		names.push_back(itr->first);
	}
	
	return names;
}

map<string, string> Device::getState() {
	return state;
}

bool Device::getStateValue(string name, string *out) {
	
	map<string,string>::iterator itr;
	
	if (getStateFieldIterator(name, &itr)) {
		*out = itr->second;
		return true;
	}
	
	return false;
}

vector<string> Device::getCommands() {
	return commands;
}

void Device::setCommunicationProtocols(vector<string> protocols) {
	communicationProtocols = protocols;
}
		
vector<string> Device::getCommunicationProtocols() {
	return communicationProtocols;
}

bool Device::changeStateValue(string name, string value) {
	map<string,string>::iterator itr;
	
	if (getStateFieldIterator(name, &itr)) {
		itr->second = value;
		return true;
	}
	
	return false;
}

bool Device::doHeartbeat(string timestamp) {
	return changeStateValue(HEARTBEAT, timestamp);
}

/**** Private Functions ***/#

bool Device::getStateFieldIterator(string name, map<string,string>::iterator* out) {
	map<string,string>::iterator itr = state.find(name);
	if (itr != state.end()) {
		*out = itr;
		return true;
	}
	return false;
}
