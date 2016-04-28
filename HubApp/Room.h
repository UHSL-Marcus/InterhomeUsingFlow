/********************************************************************
// ***************************** Room.h *****************************
/*******************************************************************/

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <string>

#include "RoomDeviceMapManager.h"

using std::vector;
using std::string;

class Room {
	public:
		/** Room Constructor.
			*
			* @param _roomID 	ID of the room
			* @param _roomName	Name of the room
			*/
		Room(string _roomID, string _roomName);
		
		/** Get the ID of the room.
			*
			* @return string	Room ID 
			*/	
		string getID();
		
		/** Get the name of the room.
			*
			* @return string	Room Name 
			*/	
		string getName();
		
	private:
		string roomID;
		string roomName;
};

#endif /* ROOM_H */