/********************************************************************
// ************************ DeviceManager.h *************************   
/*******************************************************************/

#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <string>
#include <vector>

#include "CommandHandler.h"
#include "Device_Socket.h"
#include "XMLUtil.h"

using std::vector;
using std::string;

class DeviceManager : public ICommandCallback {
	public:
		/** Constructor.
			*
			*/
		DeviceManager();
		
		/** Add the callback functions pairs to the command handler
			*
			*/
		void setCommandCallbacks();
		
		/** Get COPY of the vector with all the devices stored. Modifing this returned vector will NOT effect the stored devices!
			*
			* @return 	A vector holding all the device objects
			*/
		vector<Device> getDevices();
		
		/** Get COPY of the vector with all the pending devices stored. Modifing this returned vector will NOT effect the stored pending devices!
			*
			* @return 	A vector holding all the pending device objects
			*/
		vector<Device> getPendingDevices();
		
		/** Get a COPY of a single device. Modifing this device will not effect the device store.
			*
			* @param id 	Device ID
			* @param *out	Pointer to a device object, to hold the copy 	
			* @return bool 	Device was succesfully found
			*/
		bool getDevice(string id, Device *out);
		
		/** Static callback function for the command to move a pending device to a full added device.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void addPendingDevice(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to move a pending device to a full added device.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void addPendingDevice(XMLParse params);
		
		/** Static callback function for the command to remove a device.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void removeDevice(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to remove a device.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void removeDevice(XMLParse params);
		
		/** Static callback function for the command to action a device heartbeat.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void deviceHeartbeat(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to action a device heartbeat.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void deviceHeartbeat(XMLParse params);
		
		/** Static callback function for the command announcing a new device.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void newDevicePresence(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command announcing a new device.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void newDevicePresence(XMLParse params);
	private:
		vector<Device> allDevices;
		vector<Device> pendingDevices;
		int getDeviceIndexID(string id);
		int getDeviceIndexMAC(string mac);
		int getPendingDeviceIndex(string mac);
		
		// timer to remove pending devices after a while
};

extern DeviceManager deviceManager;

#endif /* DEVICE_MANAGER_H */