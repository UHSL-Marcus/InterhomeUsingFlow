/********************************************************************
// *********************** UIDeviceManager.h ************************   
/*******************************************************************/

#ifndef UI_DEVICE_MANAGER_H
#define UI_DEVICE_MANAGER_H

#include <string>
#include <vector>

#include "Managers_Handlers.h"
#include "UIDevice.h"
#include "XMLUtil.h"

using std::vector;
using std::string;

class UIDeviceManager : public ICommandCallback {
	public:
		/** Constructor.
			*
			*/
		UIDeviceManager();
		
		/** Add the callback functions pairs to the command handler
			*
			*/
		void setCommandCallbacks();
		
		/** Static callback function for the command to add a UIDevice.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void addUIDevice(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to move a pending device to a full added device.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void addUIDevice(XMLParse params);
		
		/** Static callback function for the command to remove a UIDevice.
			* This function only calls the correspoding member function.
			*
			* @param *parent	Pointer to the object that set this callback 
			* @param params		XMLParse object holding the command infomation 	
			*/
		static void removeUIDevice(ICommandCallback *parent, XMLParse params);
		
		/** The member function for the command to move a pending device to a full added device.
			*
			* @param params		XMLParse object holding the command infomation
			*/
		void removeUIDevice(XMLParse params);
		
		/** Get COPY of the vector with all the UI devices stored. Modifing this returned vector will NOT effect the stored UI devices!
			*
			* @return 	A vector holding all the UI device objects
			*/
		vector<UIDevice> getUIDevices();
		
		/** Get a COPY of a single UI device. Modifing this device will not effect the UI device store.
			*
			* @param id 	UIDevice ID
			* @param *out	Pointer to a UI device object, to hold the copy 	
			* @return bool 	UIDevice was succesfully found
			*/
		bool getUIDevice(string id, UIDevice *out);
		
		void uiDeviceBool(string id, bool result, string guid);
		
		void uiDeviceMessage(string message, string id = "", string guid = "");
		
		void uiDeviceCommand(string cmd, string data, string id = "", string guid = "");
		
	private:
		vector<UIDevice> allUIDevices;
		int getUIDeviceIndex(string id);
};

extern UIDeviceManager uiDeviceManager;

#endif /* UI_DEVICE_MANAGER_H */
