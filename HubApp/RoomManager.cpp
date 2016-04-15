/********************************************************************
// ************************ RoomManager.cpp *************************   
/*******************************************************************/

#include "RoomManager.h"

using namespace std;

RoomManager::RoomManager() {
	roomCount = 0;
	commandHandler.addCallback("AddNewRoom", addNewRoom);
	commandHandler.addCallback("RemoveRoom", removeRoom);
}

void RoomManager::addNewRoom() {
	bool success = false;
	
	Room *room = new Room("id", "name");
	
	int idx = getRoomIndex("id");
	if (idx < 0) {
		allRooms[roomCount] = room;
		roomCount++;
		success = true;
	}
	
	// send success info to requesting device
}

Room** RoomManager::getRooms() {
	return allRooms;
}

Room* RoomManager::getRoom(char * id) {
	Room* room = NULL;
	
	int idx = getRoomIndex(id);
	if (idx > -1)
		room = allRooms[i];

	return room;
}

void RoomManager::removeRoom() {
	bool success = false;
	
	int idx = getRoomIndex("id");
	
	if (idx > -1) {
		for (int i = idx; i < roomCount; i++) {
			allRooms[i] = allRooms[i+1]; // I think need to destroy the room object properly too...
		}
		roomCount--;
		success = true;
	}
	
	// send success to requesting device
}

int getRoomIndex(char * id) {
	int idx = -1;
	for (int i = 0; i < roomCount; i++) {
		size_t roomIDLen = strlen(allRooms[i]->getID());
		if (strncmp(id, allRooms[i]->getID(), roomIDLen) == 0 && strlen(id) == roomIDLen) {
			idx = i;
		}
	}
	
	return idx;
}

RoomManager roomManager;