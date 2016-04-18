/********************************************************************
// ************************* RoomManager.h **************************   
/*******************************************************************/

#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <cstring>
#include <vector>

#include "CommandHandler.h"
#include "Room.h"

using std::vector;

class RoomManager : public ICommandCallback {
	public:
		RoomManager();
		vector<Room*> getRooms();
		Room* getRoom(char * id);
		static void addNewRoom(ICommandCallback *parent);
		void addNewRoom();
		static void removeRoom(ICommandCallback *parent);
		void removeRoom();
		
	private:
		vector<Room*> allRooms;
		int getRoomIndex(char * id);
};

extern RoomManager roomManager;

#endif /* ROOM_MANAGER_H */