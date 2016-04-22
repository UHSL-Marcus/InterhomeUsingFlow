/********************************************************************
// **************************** main.cpp ****************************
/*******************************************************************/

#include "DeviceManager_TEST.h"

namespace DeviceManager_TEST {
	void printRooms() {
		cout << "\nRoom device mapping:\n";
		
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


	void printDevices() {
		
		vector<Device> pending = deviceManager.getPendingDevices();
		vector<Device> devices = deviceManager.getDevices();
		
		cout << "\nPending: ";
		
		for (int i = 0; i < pending.size(); i++) {
			cout << pending[i].getID() + " ";
		}
		
		cout << "\nDevices: ";
		for (int i = 0; i < devices.size(); i++) {
			cout << devices[i].getID() + "(" + devices[i].getName() + ") ";
		}
		
		cout << "\n";
	}
}
using namespace DeviceManager_TEST;


void doDeviceManager_test() {
	
	XMLParse add1("<packet><data><room_name>room1</room_name></data></packet>");
	XMLParse add2("<packet><data><room_name>room2</room_name></data></packet>");
	
	XMLParse heart1("<packet><from>device1MAC</from><data><device_type>Socket</device_type></data></packet>");
	XMLParse heart2("<packet><from>device2MAC</from><data><device_type>Thermo</device_type></data></packet>");
	
	XMLParse pending1("<packet><data><temp_id>device1MAC</temp_id><room_id>room1</room_id><device_name>device1</device_name></data></packet>");
	XMLParse pending2("<packet><data><temp_id>device2MAC</temp_id><room_id>room2</room_id><device_name>device2</device_name></data></packet>");
	
	XMLParse remove("<packet><data><device_id>device1</device_id></data></packet>");
	
	commandHandler.handleCmd("AddNewRoom", add1);
	commandHandler.handleCmd("AddNewRoom", add2);
	
	cout << "added rooms\n";
	printRooms();
	
	commandHandler.handleCmd("DeviceHeartbeat", heart1);
	commandHandler.handleCmd("DeviceHeartbeat", heart2);
	
	cout << "done heartbeats\n";
	printDevices();
	
	commandHandler.handleCmd("AddPendingDevice", pending1);
	commandHandler.handleCmd("AddPendingDevice", pending2);
	
	cout << "Added pending\n";
	printDevices();
	printRooms();
	
	commandHandler.handleCmd("RemoveDevice", remove);
	
	cout << "removed device 1\n";
	printDevices();
	printRooms();
	
}