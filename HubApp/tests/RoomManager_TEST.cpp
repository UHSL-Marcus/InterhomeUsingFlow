/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

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
	
	XMLParse addUI("<packet><from>tester</from><data><ui_device_name>ui device 1 name</ui_device_name></data></packet>");
	commandHandler.handleCmd("AddUIDevice", addUI);
	

	XMLParse add1("<packet><guid>0</guid><from>tester</from><to>hub</to><data><room_name>room1</room_name></data></packet>");
	XMLParse add2("<packet><guid>1</guid><from>tester</from><to>hub</to><data><room_name>room2</room_name></data></packet>");
	XMLParse remove("<packet><guid>2</guid><from>tester</from><to>hub</to><data><room_id>room1</room_id></data></packet>");
	
	commandHandler.handleCmd("AddNewRoom", add1);
	commandHandler.handleCmd("AddNewRoom", add2);
	
	cout << "added rooms\n";
	printRooms();
	
	commandHandler.handleCmd("RemoveRoom", remove);
	
	cout << "removed room1\n";
	printRooms();
	
}