/********************************************************************
// **************************** Room.cpp ****************************
/*******************************************************************/


#include "Room.h"

/**** Public Functions ***/

Room::Room(string _roomID, string _roomName) : roomID(_roomID), roomName(_roomName) {
	roomDeviceMapManager.addRoom(roomID);
}

string Room::getID() {
	return roomID;
}
string Room::getName() {
	return roomName;
}

/**** Private Functions ***/
