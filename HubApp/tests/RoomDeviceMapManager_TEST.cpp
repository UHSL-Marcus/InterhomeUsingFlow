/********************************************************************
// **************************** main.cpp ****************************
/*******************************************************************/

#include "RoomDeviceMapManager_TEST.h"

namespace RoomDeviceMapManager_TEST {
	void printRooms() {
		cout << "\nRooms:\n";
		
		vector<string> rooms = roomDeviceMapManager.getRooms();
		
		for (int i = 0; i < rooms.size(); i++) {
			
			cout << rooms[i] << " => ";
			
			vector<string> devices;
			
			if (roomDeviceMapManager.getRoomDevices(rooms[i], &devices)) {
				for (int s = 0; s < devices.size(); s++) {
					cout << devices[s] + "\n";
				}
			}
			
			cout << "\n";
		}
	}
}
using namespace RoomDeviceMapManager_TEST;

void doRoomDeviceMapManager_test() {
	
	
	roomDeviceMapManager.addRoom("room1");
	roomDeviceMapManager.addRoom("room2");
	cout << "Added rooms\n";
	printRooms();
	 
	roomDeviceMapManager.addDevice("room1", "deviceA1");
	roomDeviceMapManager.addDevice("room1", "deviceB1");
	roomDeviceMapManager.addDevice("room2", "deviceA2");
	roomDeviceMapManager.addDevice("room2", "deviceB2");
	roomDeviceMapManager.addDevice("room2", "deviceC2");
	cout << "Added devices\n";
	printRooms();
	
	string room;
	roomDeviceMapManager.getDeviceRoom("deviceB2", &room);
	cout << "deviceB2 is in: " + room << "\n";
	
	roomDeviceMapManager.removeDevice("deviceA2");
	cout << "removed devicesA2\n";
	printRooms();
	
	roomDeviceMapManager.removeRoom("room1");
	cout << "removed room1\n";
	printRooms();
	
}