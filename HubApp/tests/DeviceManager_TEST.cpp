/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "DeviceManager_TEST.h"

namespace DeviceManager_TEST {
	
	void printRooms() {
		cout << "\nRoom device mapping:\n";
		
		vector<string> rooms = roomDeviceMapManager.getRooms();
		
		for (int i = 0; i < rooms.size(); i++) {
			Room *room;
			roomManager.getRoom(rooms[i], room);
			
			cout << "(ID: " << room->getID() << ", Name: " << room->getName() << ") => ";
			
			vector<string> devices;
			
			if (roomDeviceMapManager.getRoomDevices(rooms[i], &devices)) {
				for (int s = 0; s < devices.size(); s++) {
					Device *device;
					deviceManager.getDevice(devices[s], device);
					
					cout << "(ID: " << device->getID() << ", Name: " << device->getName() << ")\n";
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
		vector<string> proto = device.getCommunicationProtocols();
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
		
		cout << "\nDevices Pending: \n";
		
		for (int i = 0; i < pending.size(); i++) {
			printDeviceInfo(pending[i]); cout << "\n\n";
		}
		
		cout << "\nDevices Active: \n";
		for (int i = 0; i < devices.size(); i++) {
			printDeviceInfo(devices[i]); cout << "\n\n";
		}
		
		cout << "\n";
	}
	
	
}
using namespace DeviceManager_TEST;


void doDeviceManager_test() {
	
	XMLParse addUI("<packet><from>tester</from><data><ui_device_name>ui device 1 name</ui_device_name></data></packet>");
	commandHandler.handleCmd("AddUIDevice", addUI);
	
	XMLParse addRoom1("<packet><guid>0</guid><from>tester</from><to>hub</to><data><room_name>room1</room_name></data></packet>");
	XMLParse addRoom2("<packet><guid>1</guid><from>tester</from><to>hub</to><data><room_name>room2</room_name></data></packet>");
	
	XMLParse addDevice1("<packet><guid>2</guid><to>hub</to><from>device1MAC</from><data><device_type_id>1</device_type_id><primary_communication>flow</primary_communication><backup_communication>zigbee,6lowpan</backup_communication></data></packet>");
	XMLParse addDevice2("<packet><guid>3</guid><to>hub</to><from>device2MAC</from><data><device_type_id>1</device_type_id><primary_communication>zigbee</primary_communication><backup_communication>flow,6lowpan</backup_communication></data></packet>");
	
	
	
	cout << "\n******ADDING ROOMS**********\n";
	
	commandHandler.handleCmd("AddNewRoom", addRoom1);
	commandHandler.handleCmd("AddNewRoom", addRoom2);
	printRooms();
	
	cout << "\n********SENDING NEW DEVICE PRESENCES**********\n";
	
	commandHandler.handleCmd("NewDevicePresence", addDevice1);
	commandHandler.handleCmd("NewDevicePresence", addDevice2);
	printDevices();
	
	vector<Room> rooms = roomManager.getRooms();
	stringstream ss;
	
	ss << "<packet><guid>4</guid><from>tester</from><to>hub</to><data><mac_addr>device1MAC</mac_addr><room_id>" << rooms[0].getID() << "</room_id><device_name>device1</device_name></data></packet>";
	XMLParse pending1(ss.str());
	ss.str(string());
	ss.clear();
	
	ss << "<packet><guid>4</guid><from>tester</from><to>hub</to><data><mac_addr>device2MAC</mac_addr><room_id>" << rooms[1].getID() << "</room_id><device_name>device1</device_name></data></packet>";
	XMLParse pending2(ss.str());
	ss.str(string());
	ss.clear();
	
	
	cout << "\n*********ACTIVATING PENDING DEVICES*************\n";
	commandHandler.handleCmd("AddPendingDevice", pending1);
	commandHandler.handleCmd("AddPendingDevice", pending2);
	printDevices();
	printRooms();
	
	vector<Device> devices = deviceManager.getDevices();
	ss << "<packet><guid>6</guid><from>" << devices[0].getID() << "</from><to>hub</to><timestamp>a timestamp</timestamp><data></data></packet>";
	XMLParse heart(ss.str());
	ss.str(string());
	ss.clear();
	
	ss << "<packet><guid>7</guid><from>tester</from><to>hub</to><data><device_id>" << devices[1].getID() << "</device_id><device_cmd>TestCommand</device_cmd><device_cmd_data><test_1>testing</test_1><test_2>2</test_2></device_cmd_data></data></packet>";
	XMLParse deviceCmd(ss.str());
	ss.str(string());
	ss.clear();
	
	ss << "<packet><guid>7</guid><from>" << devices[1].getID() << "</from><to>hub</to>";
	string stateChangeS = 	"<data>"
								"<state_pair>"
									"<state_name>voltage_state</state_name>"
									"<state_value>12v</state_value>"
								"</state_pair>"
								"<state_pair>"
									"<state_name>power_state</state_name>"
									"<state_value>60w</state_value>"
								"</state_pair>"
							"</data></packet>";
	
	XMLParse stateChange(ss.str() + stateChangeS);
	ss.str(string());
	ss.clear();
	
	ss << "<packet><guid>8</guid><from>tester</from><to>hub</to><data><device_id>" << devices[0].getID() << "</device_id></data></packet>";
	XMLParse remove(ss.str());
	ss.str(string());
	ss.clear();
	
	
	cout << "\n********RECIEVING HEARTBEAT FROM deviceID: " << devices[0].getID() << "*************\n";
	commandHandler.handleCmd("DeviceHeartbeat", heart);
	printDevices();
	
	cout << "\n*******SENDING COMMAND TO deviceID: " << devices[1].getID() << "****************\n";
	commandHandler.handleCmd("DeviceCommand", deviceCmd);
	//printDevices();
	
	cout << "\n********RECIEVING STATE CHANGE FROM deviceID: " << devices[1].getID() << "********************";
	cout << "\nPower to '60w' and voltage to '12v'\n";
	commandHandler.handleCmd("DeviceStateChanged", stateChange);
	printDevices();
	
	cout << "\n***********REMOVING deviceID: " << devices[0].getID() << "********************\n";
	commandHandler.handleCmd("RemoveDevice", remove);
	printDevices();
	printRooms();
	
}