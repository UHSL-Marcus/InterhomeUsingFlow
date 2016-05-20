/********************************************************************
// ***************************** Room.h *****************************
/************************************ Author: Marcus Lee ***********/

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
		/** Empty Constructor. This is only for creating a object to hold the result of getRoom() in RoomManager
			*
			*/
		Room() {};
		/** Room Constructor.
			*
			* @param _roomID 	ID of the room
			* @param _roomName	Name of the room
			*/
		Room(string _roomID, string _roomName);
		
		/** Room Copy Constructor.
			*
			*/
		Room(const Room &obj);
		
		/** Set the name of the room.
			*
			* @param name	The new name 
			*/	
		void setName(string name);
		
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