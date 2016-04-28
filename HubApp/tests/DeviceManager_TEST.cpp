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
	
	void printDeviceInfo(Device device) {
		cout << "  ID: " << device.getID() << ", MAC: " << device.getMAC() << ", Type: " << device.getType() << ", Name: " << device.getName();
		
		cout << "\n  Commands :";
		vector<string> cmds = device.getCommands();
		for (int i = 0; i < cmds.size(); i++) {
			cout << cmds[i] << " ";
		}
		
		cout << "\n  Communication Protocols: Primary => ";
		vector<string> proto = device.getcommunicationProtocols();
		if (proto.size() > 0) {
			cout << proto[0] << ", Backup => "; 
			for (int i = 1; i < proto.size(); i++) {
				cout << proto[i] << " ";
			}
		}
		
		cout << "\n  State: \n";
		map<string, string> state = device.getState();
		for (map<string,string>::iterator itr=state.begin(); itr!=state.end(); ++itr) {
			cout << "    " << itr->first << " => " << itr->second << "\n";
		}
	}


	void printDevices() {
		
		vector<Device> pending = deviceManager.getPendingDevices();
		vector<Device> devices = deviceManager.getDevices();
		
		cout << "\nPending: \n";
		
		for (int i = 0; i < pending.size(); i++) {
			printDeviceInfo(pending[i]); cout << "\n\n";
		}
		
		cout << "\nDevices: \n";
		for (int i = 0; i < devices.size(); i++) {
			printDeviceInfo(devices[i]); cout << "\n\n";
		}
		
		cout << "\n";
	}
	
	
}
using namespace DeviceManager_TEST;


void doDeviceManager_test() {
	
	
	XMLParse addRoom1("<packet><data><room_name>room1</room_name></data></packet>");
	XMLParse addRoom2("<packet><data><room_name>room2</room_name></data></packet>");
	
	XMLParse addDevice1("<packet><from>device1MAC</from><data><device_type>socket</device_type><primary_communication>flow</primary_communication><backup_communication>zigbee,6lowpan</backup_communication></data></packet>");
	XMLParse addDevice2("<packet><from>device2MAC</from><data><device_type>socket</device_type><primary_communication>zigbee</primary_communication><backup_communication>flow,6lowpan</backup_communication></data></packet>");

	XMLParse pending1("<packet><data><mac_addr>device1MAC</mac_addr><room_id>room1</room_id><device_name>device1</device_name></data></packet>");
	XMLParse pending2("<packet><data><mac_addr>device2MAC</mac_addr><room_id>room2</room_id><device_name>device2</device_name></data></packet>");
	
	XMLParse heart("<packet><timestamp>a timestamp</timestamp><from>device1</from><data></data></packet>");
	
	XMLParse remove("<packet><data><device_id>device1</device_id></data></packet>");
	
	commandHandler.handleCmd("AddNewRoom", addRoom1);
	commandHandler.handleCmd("AddNewRoom", addRoom2);
	
	cout << "\nadded rooms\n";
	printRooms();
	
	commandHandler.handleCmd("NewDevicePresence", addDevice1);
	commandHandler.handleCmd("NewDevicePresence", addDevice2);

	
	cout << "\nnew Device Presences\n";
	printDevices();
	
	commandHandler.handleCmd("AddPendingDevice", pending1);
	commandHandler.handleCmd("AddPendingDevice", pending2);
	
	cout << "\nconfirmed pending devices\n";
	printDevices();
	printRooms();
	
	commandHandler.handleCmd("DeviceHeartbeat", heart);
	cout << "\ndevice1 heartbeat\n";
	printDevices();
	
	commandHandler.handleCmd("RemoveDevice", remove);
	
	cout << "\nremoved device 1\n";
	printDevices();
	printRooms();
	
}