/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "Device_TEST.h"

namespace Device_TEST{
	
	#include "../Device.h"
	
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
	
	void printState(Device device) {
		cout << "\n State field names: ";
		vector<string> names = device.getStateFieldNames();
		for (int i = 0; i < names.size(); i++) {
			cout << names[i] << " ";
		}
		
		cout << "\n Values: \n";
		map<string, string> state = device.getState();
		for (map<string,string>::iterator itr=state.begin(); itr!=state.end(); ++itr) {
			cout << itr->first << " => " << itr->second << "\n";
		}
	}
}
using namespace Device_TEST;

void doDevice_test() {
	
	XMLParse add1("<packet><data><room_name>room1</room_name></data></packet>");
	roomManager.addNewRoom(add1);
	
	cout << "\n Added Room \n";
	printRooms();
	
	Device_Socket device("socket_device1MAC");
	cout << "\ncreated device\n";
	
	cout << "\n Device MAC is: " << device.getMAC();
	cout << "\n Device Type is: " << device.getType();
	cout << "\n Commands are: ";
	vector<string> cmds = device.getCommands();
	for (int i = 0; i < cmds.size(); i++) {
		cout << cmds[i] << " ";
	}
	printState(device);
	
	device.setID("socket_deviceID");
	cout << "\n set ID to 'socket_deviceID', DeviceID: " << device.getID();
	
	device.setName("socket_device_name");
	cout << "\n set name to 'socket_device_name', DeviceName: " << device.getName();
	
	device.setRoom("room1");
	cout << "\n Added device to room 'room1', DeviceRoom: " << device.getRoom();
	printRooms();
	
	device.changeStateValue("connected_state", "on");
	string val;
	device.getStateValue("connected_state", &val);
	cout << "\n changed 'connected_state' to 'on' (Device_Socket should preappend '(socket)' to the added value), 'connected_state' value: " << val;
	printState(device);
	
	time_t t = time(0);
	struct tm now = *localtime(&t);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &now);
	device.doHeartbeat(buf);
	
	val = "";
	device.getStateValue("heartbeat_state", &val);
	cout << "\n heartbeat set as current time. 'heartbeat_state' value : " << val;
	printState(device);
	
	device.removeFromRoom();
	cout << "\n Removed device from its room. Device room: " << device.getRoom();
	printRooms();
	
	
}