/********************************************************************
// **************************** Room.cpp ****************************
/*******************************************************************/


#include "Room.h"


Room::Room(char* _roomID, char* _roomName) {
	roomID = _roomID;
	roomName = _roomName;
}

bool Room::addDevice(char * id) {
	bool success = false;
	
	if (!containsDevice(id)) {
		allDevices.push_back(id);
		success = true;
	}
	
	return success;
}

vector<char*> Room::getDevices() {
	return allDevices;
}

char* Room::getID() {
	return roomID;
}

bool Room::removeDevice(char * id) {
	bool success = false;
	
	int idx = getDeviceIndex(id);
	
	//if (idx > -1) 
		//allDevices.erase(idx);
	
	
	return success;
}

bool Room::containsDevice(char * id) {
	return getDeviceIndex(id) > -1 ? true : false;
}

int Room::getDeviceIndex(char * id) {
	int idx = -1;
	
	for (int i = 0; i < allDevices.size(); i++) {
		size_t idLen = strlen(allDevices[i]);
		if (strncmp(allDevices[i], id, idLen) == 0 && strlen(id) == idLen) {
			idx = i;
		}
	}
	
	return idx;
}