/********************************************************************
// **************************** Room.cpp ****************************
/************************************ Author: Marcus Lee ***********/


#include "Room.h"

/**** Public Functions ***/

Room::Room(string _roomID, string _roomName) : roomID(_roomID), roomName(_roomName) {
	roomDeviceMapManager.addRoom(roomID);
}

void Room::setName(string name) {
	roomName = name;
}

string Room::getID() {
	return roomID;
}
string Room::getName() {
	return roomName;
}

/**** Private Functions ***/
