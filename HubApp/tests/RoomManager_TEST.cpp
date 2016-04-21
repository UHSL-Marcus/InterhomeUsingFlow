/********************************************************************
// **************************** main.cpp ****************************
/*******************************************************************/

#include "XMLUtil.h"
#include "CommandHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include <iostream>
#include <cstring>
#include <vector>

using std::cout;
using std::string;
using std::vector;

void printRooms() {
	
	cout << "\nrooms: ";
	vector<Room> rooms = roomManager.getRooms();
	
	for (int i = 0; i < rooms.size(); i++) {
		cout << rooms[i].getID() + " ";
	}
	
	cout << "\n";
}


int main(void) {
	
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
	
	return 0;
}