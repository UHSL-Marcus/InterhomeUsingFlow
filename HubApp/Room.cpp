/********************************************************************
// **************************** Room.cpp ****************************
/*******************************************************************/


#include "Room.h"


Room::Room(string _roomID, string _roomName) {
	roomID = _roomID;
	roomName = _roomName;
}

bool Room::addDevice(string id) {
	bool success = false;
	
	if (!containsDevice(id)) {
		allDevices.push_back(id);
		success = true;
	}
	
	return success;
}

vector<string> Room::getDevices() {
	return allDevices;
}

string Room::getID() {
	return roomID;
}
string Room::getName() {
	return roomName;
}

bool Room::removeDevice(string id) {
	bool success = false;
	
	int idx = getDeviceIndex(id);
	
	if (idx > -1) 
		allDevices.erase(allDevices.begin()+idx);
	
	
	return success;
}

bool Room::containsDevice(string id) {
	return getDeviceIndex(id) > -1 ? true : false;
}

int Room::getDeviceIndex(string id) {
	int idx = -1;
	
	for (int i = 0; i < allDevices.size(); i++) {
		if (allDevices[i] == id && id.size() == allDevices[i].size()) {
			idx = i;
		}
	}
	
	return idx;
}