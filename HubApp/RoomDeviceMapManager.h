/********************************************************************
// ************************ RoomDeviceMapManager.h *************************   
/*******************************************************************/

#ifndef ROOM_DEVICE_MAP_MANAGER_H
#define ROOM_DEVICE_MAP_MANAGER_H

#include <cstring>
#include <vector>
#include <map>

#include "CommandHandler.h"

using std::vector;
using std::string;
using std::map;

class RoomDeviceMapManager {
	public:
		/** Constructor.
			*
			*/
		RoomDeviceMapManager();
		
		/** Add a room to the map
			*
			* @param id 	ID of the room
			* @return bool 	operation success
			*/
		bool addRoom(string id);
		
		/** Remove a room from the map.
			*
			* @param id 	ID of the room
			* @return bool 	operation success
			*/
		bool removeRoom(string id);
		
		/** Add a device to a room.
			*
			* @param room_id 	ID of the room
			* @param device_id	ID of the device
			* @return bool 		operation success
			*/
		bool addDevice(string room_id, string device_id);
		
		/** Remove a device from the map.
			*
			* @param device_id 	ID of the device
			* @return bool 		operation success
			*/
		bool removeDevice(string device_id);
		
		/** Returns whether a device is mapped to a room.
			*
			* @param id 	ID of the device
			* @return bool 	device is mapped
			*/
		bool deviceHasRoom(string id);
		
		/** Get the ID of the room a device is mapped to.
			*
			* @param id 	ID of the device
			* @param *out	pointer to string to contain the returned room ID
			* @return bool 	operation success
			*/
		bool getDeviceRoom(string id, string* out);
		
		/** get a COPY of the vector of devices mapped to a room. Modifing this returned vector will NOT effect the map!
			*
			* @param id 	ID of the room
			* @param *out	pointer to vector<string> to contain the returned device collection
			* @return bool 	operation success
			*/
		bool getRoomDevices(string id, vector<string>* out);
		
		/** Get all the room IDs.
			*
			* @return vector<string> 	Collection of room IDs
			*/
		vector<string> getRooms();
		
	private:
		map<string, vector<string> > roomDeviceMap;
		bool getDeviceIndexAndRoomIterator(string id, map<string,vector<string> >::iterator* out, int *idxOut);
		bool getRoomIterator(string id, map<string,vector<string> >::iterator* out);
};

extern RoomDeviceMapManager roomDeviceMapManager;

#endif /* ROOM_DEVICE_MAP_MANAGER_H */