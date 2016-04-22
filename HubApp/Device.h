/********************************************************************
// **************************** Device.h ****************************          
/*******************************************************************/

#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>

#include "RoomDeviceMapManager.h"

using std::vector;
using std::string;

class Device {
	public:
		/** Constructor.
			*
			*@param id 			Device ID
			*@param type 		The device type
			*/
		Device(string id, string type);
		
		/** Set the ID of this device
			*
			*@param id 			The new device ID
			*/
		void setID(string id);
		
		/** Set the name of this device
			*
			*@param name 		The new device name
			*/
		void setName(string name);
		
		/** Set the room of this device
			*
			*@param room_id 	The new room ID
			*/
		void setRoom(string room_id);
		
		/** Get the ID of this device
			*
			*@return string 	The device ID
			*/
		string getID();
		
		/** Get the name of this device
			*
			*@return string 	The device name
			*/
		string getName();
		
		/** Get the room of this device
			*
			*@return string 	The room ID
			*/
		string getRoom();
		
		/** Remove this device from its room
			*
			*@return bool 		Removed successfully
			*/
		bool removeFromRoom();
	private:
		string deviceID;
		string deviceName;
		string deviceType;
};

#endif /* DEVICE_H */