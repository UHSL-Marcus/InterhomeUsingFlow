/********************************************************************
// ************************ RoomManager.cpp *************************   
/*******************************************************************/



#include "RoomManager.h"

/**** Public Functions ***/

RoomManager::RoomManager() {
	commandHandler.addCallback("AddNewRoom", RoomManager::addNewRoom, this);
	commandHandler.addCallback("RemoveRoom", RoomManager::removeRoom, this);
}

void RoomManager::addNewRoom(ICommandCallback *parent, XMLParse params) {
	(static_cast<RoomManager*>(parent))->addNewRoom(params);
}
void RoomManager::addNewRoom(XMLParse params) {

	bool success = false;
	
	
	
	string name;
	if (params.GetStringNode(ROOM_NAME_PATH, &name)) {
	
		// Need to generate ID, probably from webservice
		Room room(name, name); // temp
		
		int idx = getRoomIndex(name);
		if (idx < 0) {
			allRooms.push_back(room);
			success = true;
		}
	}
	
	// send success info to requesting device
}

vector<Room> RoomManager::getRooms() {
	return allRooms;
}

Room* RoomManager::getRoom(string id) {
	Room *room = NULL;
	
	int idx = getRoomIndex(id);
	if (idx > -1)
		room = &allRooms[idx];

	return room;
}

void RoomManager::removeRoom(ICommandCallback *parent, XMLParse params) {
	(static_cast<RoomManager*>(parent))->removeRoom(params);
}
void RoomManager::removeRoom(XMLParse params) {
	bool success = false;
	
	string id;
	if (params.GetStringNode(ROOM_ID_PATH, &id)) {
		
		int idx = getRoomIndex(id);
		if (idx > -1) 
			allRooms.erase(allRooms.begin()+idx);
		
			
	
	}
	
	// send success to requesting device
}

/**** Private Functions ***/

int RoomManager::getRoomIndex(string id) {
	int idx = -1;
	for (int i = 0; i < allRooms.size(); i++) {
		string roomID = allRooms[i].getID();
		if (id == roomID && id.size() == roomID.size()) {
			idx = i;
		}
	}
	
	return idx;
}

RoomManager roomManager;