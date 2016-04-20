/********************************************************************
// ************************ DeviceManager.h *************************   
/*******************************************************************/

#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <cstring>
#include <vector>

#include "CommandHandler.h"
#include "Device.h"
#include "XMLUtil.h"

using std::vector;
using std::string;

class DeviceManager {
	public:
		DeviceManager();
		vector<Device> getDevices();
		Device* getDevice(string id);
		static void addPendingDevice(ICommandCallback *parent, XMLParse params);
		void addPendingDevice(XMLParse params);
		static void removeDevice(ICommandCallback *parent, XMLParse params);
		void removeDevice(XMLParse params);
		static void deviceHeartbeat(ICommandCallback *parent, XMLParse params);
		void deviceHeartbeat(XMLParse params);
	private:
		vector<Device> allDevices;
		vector<Device> pendingDevices;
		int getDeviceIndex(string id);
		int getPendingDeviceIndex(string id);
};

extern DeviceManager deviceManager;

#endif /* DEVICE_MANAGER_H */