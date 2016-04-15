/********************************************************************
// ************************* RoomManager.h **************************   
/*******************************************************************/

#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include "CommandHandler.h"

class RoomManager {
	public:
		RoomManager();
		void addNewRoom(); // to be a callback method
		Room*[] getRooms();
		Room* getRoom(char * id);
		void removeRoom(); // to be a callback method
		
	private:
		Room** allRooms;
		int roomCount;
}

extern RoomManager roomManager;

#endif /* ROOM_MANAGER_H */