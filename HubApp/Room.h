/********************************************************************
// ***************************** Room.h *****************************
/*******************************************************************/

#ifndef ROOM_H
#define ROOM_H


class Room {
	public:
		Room(char* _roomID, char* _roomName);
		bool addDevice(char * id); 
		char** getDevices();
		bool removeDevice(char * id); 
		bool containsDevice(char * id);
		char* getID();
		
	private:
		char * roomID;
		char * roomName;
		char ** allDevices;	
		int deviceCount;
}

#endif /* ROOM_MANAGER_H */