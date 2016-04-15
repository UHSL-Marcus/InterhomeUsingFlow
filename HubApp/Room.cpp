/********************************************************************
// **************************** Room.cpp ****************************
/*******************************************************************/

#include "Room.h"

using namespace std;

Room::Room(char* _roomID, char* _roomName) {
	strcpy(roomID, _roomID);
	stpcpy(roomname, _roomName);
	deviceCount = 0;
}

bool Room::addDevice(char * id) {
	bool success = false;
	
	if (!containsDevice(id)) {
		strcpy(allDevices[deviceCount], id);
		deviceCount++;
		success = true;
	}
	
	return success;
}

char** Room::getDevices() {
	return allDevices;
}

char* Room::getID() {
	return roomID;
}

bool removeDevice(char * id) {
	bool success = false;
	
	int idx = getRoomIndex(id);
	
	if (idx > -1) {
		for (int i = idx; i < deviceCount; i++) {
			allDevices[i] = allDevices[i+1];
		}
		deviceCount--;
		success = true;
	}
	
	return success;
}

bool Room::containsDevice(char * id) {
	return getRoomIndex(id) > -1 ? true : false;
}

int getRoomIndex(char * id) {
	int idx = -1;
	
	for (int i = 0; i < deviceCount; i++) {
		size_t idLen = strlen(allDevices[i]);
		if (strncmp(allDevices[i], id, idLen) == 0 && strlen(id) == idLen) {
			idx = i;
		}
	}
	
	return idx;
}