/********************************************************************
// ************************* RoomManager.h **************************   
/*******************************************************************/

#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <string>
#include <vector>

#include "CommandHandler.h"
#include "Room.h"
#include "XMLUtil.h"

using std::vector;
using std::string;

class RoomManager : public ICommandCallback {
	public:
		RoomManager();
		
		/** Add the callback functions pairs to the command handler
			*
			*/
		void setCommandCallbacks();
		
		/** Get COPY of the vector with all the rooms stored. Modifing this returned vector will NOT effect the stored rooms!
			*
			* @return 	A vector holding all the room objects
			*/
		vector<Room> getRooms();
		
		/** Get a COPY of a single room. Modifing this room will not effected the room store.
			*
			* @param id 	Room ID
			* @param *out	pinter to a room object, to hold the copy 	
			* @return bool 	Room was succesfully found
			*/
		bool getRoom(string id, Room *out);
		
		/** Static callback function for the command to add a new room.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void addNewRoom(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to add a new room.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void addNewRoom(XMLParse params);
		
		/** Static callback function for the command to remove a room.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void removeRoom(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to remove a room.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void removeRoom(XMLParse params);
		
	private:
		vector<Room> allRooms;
		
		/** Get the index of a room within the storage vector
			*
			* @param id		Room ID
			* @return int 	The index of the room within the storage vector (-1 if not present)
			*/
		int getRoomIndex(string id);
};

/** The refrence of RoomManager to be used.
    *
    */
extern RoomManager roomManager;

#endif /* ROOM_MANAGER_H */