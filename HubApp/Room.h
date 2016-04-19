/********************************************************************
// ***************************** Room.h *****************************
/*******************************************************************/

#ifndef ROOM_H
#define ROOM_H

#include <cstring>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Room {
	public:
		/** Room Constructor.
			*
			* @param _roomID 	ID of the room
			* @param _roomName	Name of the room
			*/
		Room(string _roomID, string _roomName);
		
		/** Add a device ID to the list of devices.
			*
			* @param id 	Device ID
			* @return bool	Whether the operation was successful 
			*/
		bool addDevice(string id); 
		
		/** Add a device ID to the list of devices.
			*
			* @return vector<string>	A vector holding all the device ID's
			*/
		vector<string> getDevices();
		
		/** Remove a device ID to the list of devices.
			*
			* @param id 	Device ID
			* @return bool	Whether the operation was successful 
			*/
		bool removeDevice(string id);
		
		/** Check if a device is contrained in the list of devices.
			*
			* @param id 	Device ID
			* @return bool	true for Contained, otherwsise false 
			*/		
		bool containsDevice(string id);
		
		/** Get the ID of the room.
			*
			* @return string	Room ID 
			*/	
		string getID();
		
		/** Get the name of the room.
			*
			* @return string	Room Name 
			*/	
		string getName();
		
	private:
		string roomID;
		string roomName;
		vector<string> allDevices;
		
		/** Get the index of a device within the storage vector
			*
			* @param id		Device ID
			* @return int 	The index of the device within the storage vector (-1 if not present)
			*/
		int getDeviceIndex(string id);
};

#endif /* ROOM_H */