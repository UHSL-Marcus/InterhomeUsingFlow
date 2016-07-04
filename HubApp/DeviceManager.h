/********************************************************************
// ************************ DeviceManager.h *************************   
/************************************ Author: Marcus Lee ***********/

#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <string>
#include <vector>
#include <mutex>

#include "Managers_Handlers.h"
#include "Device_Socket.h"
#include "XMLUtil.h"

using std::vector;
using std::string;
using std::mutex;
using std::unique_lock;

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
		
		/** Static callback function for the command to send a command to a device.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void deviceCommand(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to send a command to a device.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void deviceCommand(XMLParse params);
		
		/** Static callback function for the command to update the device state.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void deviceStateChange(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to update the device state.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void deviceStateChange(XMLParse params);
		
	private:
		mutex allDevicesMutex;
		mutex pendingDevicesMutex;
		
		vector<Device> allDevices;
		vector<Device> pendingDevices;
		
		template<typename... Mutexes>
		int getDeviceIndexID(string id, unique_lock<mutex> *outLock, Mutexes& ...mutexes);
		int getDeviceIndexID(string id, unique_lock<mutex> *outLock);
		int getDeviceIndexID(string id);
		
		template<typename... Mutexes>
		int getDeviceIndexMAC(string mac, unique_lock<mutex> *outLock, Mutexes& ...mutexes);
		int getDeviceIndexMAC(string mac, unique_lock<mutex> *outLock);
		int getDeviceIndexMAC(string mac);
		
		template<typename... Mutexes>
		int getPendingDeviceIndex(string mac, unique_lock<mutex> *outLock, Mutexes& ...mutexes);
		int getPendingDeviceIndex(string mac, unique_lock<mutex> *outLock);
		int getPendingDeviceIndex(string mac);
		
		// timer to remove pending devices after a while
};

extern DeviceManager deviceManager;

template<typename... Mutexes>
int DeviceManager::getPendingDeviceIndex(string mac, unique_lock<mutex> *outLock, Mutexes& ...mutexes) {
	unique_lock<mutex> guard(pendingDevicesMutex, std::defer_lock);
	std::lock(guard, mutexes...);
	
	return getPendingDeviceIndex(mac, outLock);
}

template<typename... Mutexes>
int DeviceManager::getDeviceIndexID(string id, unique_lock<mutex> *outLock, Mutexes& ...mutexes) {
	unique_lock<mutex> guard(allDevicesMutex, std::defer_lock);
	std::lock(guard, mutexes...);
	
	return getDeviceIndexID(id, outLock);
}

template<typename... Mutexes>
int DeviceManager::getDeviceIndexMAC(string mac, unique_lock<mutex> *outLock, Mutexes& ...mutexes) {
	unique_lock<mutex> guard(allDevicesMutex, std::defer_lock);
	std::lock(guard, mutexes...);
	
	return getDeviceIndexMAC(mac, outLock);
}

#endif /* DEVICE_MANAGER_H */