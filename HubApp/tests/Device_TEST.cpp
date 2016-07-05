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
					cout << devices[s] + " ";
				}
			}
			
			cout << "\n";
		}
	}
	
	void printState(Device device) {
		cout << "\nState field names: ";
		vector<string> names = device.getStateFieldNames();
		for (int i = 0; i < names.size(); i++) {
			cout << names[i] << " ";
		}
		
		cout << "\nState values: \n";
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
	threadManager.joinAllThreads();
	
	if (roomDeviceMapManager.getRooms().size() > 0) {
	
		cout << "\n******ADDING ROOM**********\n";
		printRooms();
		string roomID = roomDeviceMapManager.getRooms()[0];
		
		Device_Socket device("socket_device1MAC");
		cout << "\n******CREATED DEVICE**********\n";
		
		cout << "\nDevice MAC is: " << device.getMAC();
		cout << "\nDevice Type is: " << device.getType();
		cout << "\nCommands are: ";
		vector<string> cmds = device.getCommands();
		for (int i = 0; i < cmds.size(); i++) {
			cout << cmds[i] << " ";
		}
		printState(device);
		
		cout << "\n******UPDATING DEVICE**********\n";
		
		device.setID("socket_deviceID"); 
		cout << "\n****Set ID to 'socket_deviceID' => DeviceID: " << device.getID();

		
		device.setName("socket_device_name");
		cout << "\n****Set name to 'socket_device_name' => DeviceName: " << device.getName();

		
		if (device.setRoom(roomID)) {
			cout << "\n****Added device to room => DeviceRoom: " << device.getRoom();
			printRooms();
		} else cout << "\n****Set room failed";
		
		if (device.changeStateValue("connected_state", "on")) {
			string val;
			if(device.getStateValue("connected_state", &val)){
				cout << "\n****Changed 'connected_state' to 'on' (Device_Socket should preappend '(socket)' to the added value) => 'connected_state' value: " << val;
				printState(device);
			} else cout << "\n****Get state value 'connected_state' failed";
		} else cout << "\n****Change state failed";
		
		time_t t = time(0);
		struct tm now = *localtime(&t);
		char buf[80];
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &now);
		if(device.doHeartbeat(buf)) {
			string val = "";
			if (device.getStateValue("heartbeat_state", &val)) {
				cout << "\n****Heartbeat set as current time => 'heartbeat_state' value : " << val;
				printState(device);
			} else cout << "\n****Get state value 'heartbeat_state' failed";
		} else cout << "\n****Do heartbeat failed";
		
		cout << "\n******REMOVING DEVICE FROM ROOM**********\n";
		if (device.removeFromRoom())
			printRooms();
		else cout << "\n****Remove from room failed";
	} else cout << "\n******FAILED TO ADD ROOM**********\n";
	
	
}