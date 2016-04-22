/********************************************************************
// **************************** main.cpp ****************************
/*******************************************************************/

#include "RoomManager_TEST.h"


namespace RoomManager_TEST {
	void printRooms() {
		
		cout << "\nrooms: ";
		vector<Room> rooms = roomManager.getRooms();
		
		for (int i = 0; i < rooms.size(); i++) {
			cout << rooms[i].getID() + " ";
		}
		
		cout << "\n";
	}
}

using namespace RoomManager_TEST;


void doRoomManager_test() {
	
	XMLParse add1("<packet><data><room_name>room1</room_name></data></packet>");
	XMLParse add2("<packet><data><room_name>room2</room_name></data></packet>");
	XMLParse remove("<packet><data><room_id>room1</room_id></data></packet>");
	
	commandHandler.handleCmd("AddNewRoom", add1);
	commandHandler.handleCmd("AddNewRoom", add2);
	
	cout << "added rooms\n";
	printRooms();
	
	commandHandler.handleCmd("RemoveRoom", remove);
	
	cout << "removed room1\n";
	printRooms();
	
}