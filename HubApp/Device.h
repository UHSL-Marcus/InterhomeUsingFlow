/********************************************************************
// **************************** Device.h ****************************          
/*******************************************************************/

#ifndef DEVICE_H
#define DEVICE_H

#include <cstring>
#include <vector>

#include "RoomDeviceMapManager.h"

using std::vector;
using std::string;

class Device {
	public:
		Device(string id, string type);
		void setID(string id);
		void setName(string name);
		void setRoom(string room_id);
		string getID();
		string getName();
		string getRoom();
		bool removeFromRoom();
	private:
		string deviceID;
		string deviceName;
		string deviceType;
};

#endif /* DEVICE_H */