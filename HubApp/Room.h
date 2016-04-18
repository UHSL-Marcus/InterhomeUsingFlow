/********************************************************************
// ***************************** Room.h *****************************
/*******************************************************************/

#ifndef ROOM_H
#define ROOM_H

#include <cstring>
#include <vector>

using std::vector;

class Room {
	public:
		Room(char* _roomID, char* _roomName);
		bool addDevice(char * id); 
		vector<char*> getDevices();
		bool removeDevice(char * id); 
		bool containsDevice(char * id);
		char* getID();
		
	private:
		char * roomID;
		char * roomName;
		vector<char*> allDevices;	
		int getDeviceIndex(char * id);
};

#endif /* ROOM_H */