/********************************************************************
// **************************** Device.h ****************************          
/*******************************************************************/

#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include <map>

#include "RoomDeviceMapManager.h"
#include "state.h"

using std::vector;
using std::string;
using std::map;

class Device {
	public:
		/** Constructor. This class should not be inialised directly, only ever via a child
			*
			*@param id 			Device ID
			*@param type 		The device type
			*@param stateList 	Comma deliminated list of the non-general statefields required
			*/
		Device(string mac, string type, string stateList);
		
		/** Set the ID of this device
			*
			*@param id 			The new device ID
			*/
		void setID(string id);
		
		/** Set the MAC of this device
			*
			*@param mac 		The new device MAC
			*/
		void setMAC(string mac);
		
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
		
		/** Get the MAC of this device
			*
			*@return string 	The device MAC
			*/
		string getMAC();
		
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
		
		/** Get the room of this device
			*
			*@return string 	The room ID
			*/
		string getType();
		
		/** Get a list of the names of the state fields of this device
			*
			*@return vector<string> 	The state fields
			*/
		vector<string> getStateFieldNames();
		
		/** get a COPY of the state map for this device. Modifing this returned map will NOT effect the device state!
			*
			*@return map<string, string> 	The device state
			*/
		map<string, string> getState();
		
		/** Get a value for a single field in the device state
			*
			*@param string 		Field name
			*@param *out		Pointer to a string to hold the returned value
			*@return bool 		True if the field exists and a value was found
			*/
		bool getStateValue(string name, string *out);
		
		/** Get a list of the commands available for this device
			*
			*@return vector<string> 	List of available commands
			*/
		vector<string> getCommands();
		
		/** Set the communication protocols available for this device
			*
			*@param vector<string> 	List of communication protocols
			*/
		void setCommunicationProtocols(vector<string> protocols);
		
		/** Get a list of the communication protocols available for this device
			*
			*@return vector<string> 	List of available communication protocols
			*/
		vector<string> getCommunicationProtocols();
		
		/** Change a state value on this device
			*
			*@param string 	Field name
			*@param	string	New value
			*@return bool 	state value successfully changed
			*/
		bool changeStateValue(string name, string value);
		
		/** Update the heartbeat timestamp on this device
			*
			*@param string 	new heartbeat timestamp
			*@return bool 	Heartbeat update successful
			*/
		bool doHeartbeat(string timestamp);
		
	protected:
		vector<string> commands;
		map<string,string> state;
		vector<string> communicationProtocols;
		
	private:
		string deviceID;
		string deviceMAC;
		string deviceName;
		string deviceType;
		bool getStateFieldIterator(string name, map<string,string>::iterator* out);
		
};

#endif /* DEVICE_H */