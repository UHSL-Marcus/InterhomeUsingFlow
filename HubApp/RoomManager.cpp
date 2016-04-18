/********************************************************************
// ************************ RoomManager.cpp *************************   
/*******************************************************************/



#include "RoomManager.h"
#include <iostream>


RoomManager::RoomManager() {
	

	commandHandler.addCallback("AddNewRoom", RoomManager::addNewRoom, this);
	commandHandler.addCallback("RemoveRoom", RoomManager::removeRoom, this);
}

void RoomManager::addNewRoom(ICommandCallback *parent) {
	std::cout << "static new \n";
	(static_cast<RoomManager*>(parent))->addNewRoom();
}
void RoomManager::addNewRoom() {
	std::cout << "object new\n";
	bool success = false;
	
	Room *room = new Room("id", "name");
	
	int idx = getRoomIndex("id");
	if (idx < 0) {
		allRooms.push_back(room);
		success = true;
	}
	
	std::cout << allRooms.size() << "\n";
	for (int i = 0; i < allRooms.size(); i++) {
		std::cout << allRooms[i]->getID() << "\n";
	}
	
	// send success info to requesting device
}

vector<Room*> RoomManager::getRooms() {
	return allRooms;
}

Room* RoomManager::getRoom(char * id) {
	Room *room = NULL;
	
	int idx = getRoomIndex(id);
	if (idx > -1)
		room = allRooms[idx];

	return room;
}

void RoomManager::removeRoom(ICommandCallback *parent) {
	(static_cast<RoomManager*>(parent))->removeRoom();
}
void RoomManager::removeRoom() {
	bool success = false;
	
	int idx = getRoomIndex("id");
	//if (idx > -1)
		//allRooms.erase(idx); // I think need to destroy the room object properly too...
	
	// send success to requesting device
}

int RoomManager::getRoomIndex(char * id) {
	int idx = -1;
	for (int i = 0; i < allRooms.size(); i++) {
		size_t roomIDLen = strlen(allRooms[i]->getID());
		if (strncmp(id, allRooms[i]->getID(), roomIDLen) == 0 && strlen(id) == roomIDLen) {
			idx = i;
		}
	}
	
	return idx;
}

RoomManager roomManager;