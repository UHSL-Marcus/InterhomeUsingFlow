/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "RoomManager_TEST.h"


namespace RoomManager_TEST {
	
	
	void printRooms() {
		
		cout << "\nrooms: ";
		vector<Room> rooms = roomManager.getRooms();
		
		for (int i = 0; i < rooms.size(); i++) {
			cout << "(id: " << rooms[i].getID() + ", name: " << rooms[i].getName() << ") ";
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
	
	cout << "\n******ADDING ROOMS**********\n";
	
	commandHandler.handleCmd("AddNewRoom", add1);
	commandHandler.handleCmd("AddNewRoom", add2);
	printRooms();
	
	vector<Room> rooms = roomManager.getRooms();
	stringstream ss;
	
	ss << "<packet><guid>2</guid><from>tester</from><to>hub</to><data><room_id>" << rooms[0].getID() << "</room_id><room_name>newRoom1</room_name></data></packet>";
	XMLParse update1(ss.str());
	ss.str(string());
	ss.clear();
	
	ss << "<packet><guid>2</guid><from>tester</from><to>hub</to><data><room_id>" << rooms[1].getID() << "</room_id><room_name></room_name></data></packet>";
	XMLParse update2(ss.str());
	ss.str(string());
	ss.clear();
	
	cout << "\n******UPDATING ROOMS**********\n";
	cout << "\nupdate 'room1' to 'newRoom1'";
	commandHandler.handleCmd("UpdateRoom", update1);
	cout << "\nSend blank update to 'room2' (no change should occur)";
	commandHandler.handleCmd("UpdateRoom", update2);
	printRooms();
	
	ss << "<packet><guid>4</guid><from>tester</from><to>hub</to><data><room_id>" << rooms[1].getID() << "</room_id></data></packet>";
	XMLParse remove(ss.str());
	ss.str(string());
	ss.clear();
	
	cout << "\n******REMOVING room2**********\n";
	commandHandler.handleCmd("RemoveRoom", remove);
	printRooms();
	
}