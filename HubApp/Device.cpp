/********************************************************************
// *************************** Device.cpp ***************************          
/*******************************************************************/


#include "Device.h"

/**** Public Functions ***/

Device::Device(string id, string type) {
	deviceID = id;
	deviceType = type;
}

void Device::setID(string id) {
	deviceID = id;
}

void Device::setName(string name) {
	deviceName = name;
}

void Device::setRoom(string room_id) {
	roomDeviceMapManager.addDevice(room_id, deviceID);
}

string Device::getID() {
	return deviceID;
}

string Device::getName() {
	return deviceName;
}

string Device::getRoom() {
	string room = "";
	roomDeviceMapManager.getDeviceRoom(deviceID, &room);
	
	return room;
}

bool Device::removeFromRoom() { // put this is the destruction method?
	return roomDeviceMapManager.removeDevice(deviceID);
}

/**** Private Functions ***/
