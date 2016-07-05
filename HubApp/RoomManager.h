/********************************************************************
// ************************* RoomManager.h **************************   
/************************************ Author: Marcus Lee ***********/

#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <string>
#include <vector>
#include <exception>
/**** Private Functions ***/

#include "Managers_Handlers.h"
#include "Room.h"
#include "XMLUtil.h"
#include "HTTPRequest.h"
#include "MutexCheckable.h"

using std::vector;
using std::string;
using std::exception;
using std::unique_lock;

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
		
		/** Get a COPY of a single room. Modifing this room will not effect the room store.
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
		
		/** Static callback function for the command to update a room.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void updateRoom(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to update a room.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void updateRoom(XMLParse params);
		
	private:
		MutexCheckable allRoomsMutex;
		vector<Room> allRooms;
		
		/** Get the index of a room within the storage vector
			*
			* @param id			Room ID
			* @param *outLock	Pointer to move the lock for further use (optional)
			* @return int 		The index of the room within the storage vector (-1 if not present)
			*/
		int getRoomIndex(string id);
		int getRoomIndex(string id, unique_lock<MutexCheckable> *outLock);
};

/** The refrence of RoomManager to be used.
    *
    */
extern RoomManager roomManager;

#endif /* ROOM_MANAGER_H */