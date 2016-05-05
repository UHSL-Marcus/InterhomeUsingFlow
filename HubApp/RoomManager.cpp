/********************************************************************
// ************************ RoomManager.cpp *************************   
/*******************************************************************/



#include "RoomManager.h"

/**** Public Functions ***/

RoomManager::RoomManager() {

}

void RoomManager::setCommandCallbacks() {
	commandHandler.addCallback("AddNewRoom", RoomManager::addNewRoom, this);
	commandHandler.addCallback("RemoveRoom", RoomManager::removeRoom, this);
}

void RoomManager::addNewRoom(ICommandCallback *parent, XMLParse params) {
	(static_cast<RoomManager*>(parent))->addNewRoom(params);
}
void RoomManager::addNewRoom(XMLParse params) {

	bool success = false;
	
	string name;
	if (params.getStringNode(M_ROOM_NAME_PATH, &name)) {
		
		// Need to generate ID, probably from webservice
		Room room(name, name); // temp
		
		int idx = getRoomIndex(name);
		if (idx < 0) {
			allRooms.push_back(room);
			success = true;
		}
	}
	
	
	// send success to UI device 
	string uiID;
	string guid;
	if (params.getStringNode(M_SENDER_PATH, &uiID) && params.getStringNode(M_GUID_PATH, &guid)) {
		uiDeviceManager.uiDeviceBool(uiID, success, guid);
	}
}

vector<Room> RoomManager::getRooms() {
	return allRooms;
}

bool RoomManager::getRoom(string id, Room *out) {

	int idx = getRoomIndex(id);
	if (idx > -1) {
		*out = allRooms[idx];
		return true;
	}

	return false;
}

void RoomManager::removeRoom(ICommandCallback *parent, XMLParse params) {
	(static_cast<RoomManager*>(parent))->removeRoom(params);
}
void RoomManager::removeRoom(XMLParse params) {
	bool success = false;
	
	string id;
	if (params.getStringNode(M_ROOM_ID_PATH, &id)) {
		
		int idx = getRoomIndex(id);
		if (idx > -1) {
			allRooms.erase(allRooms.begin()+idx);
			success = true;
			// send new room configuration to UI or upon recieveing the bool it can request it?
		}
		
		
	
	}
	
	// send success to UI device 
	string uiID;
	string guid;
	if (params.getStringNode(M_SENDER_PATH, &uiID) && params.getStringNode(M_GUID_PATH, &guid)) 	
		uiDeviceManager.uiDeviceBool(uiID, success, guid);
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