/********************************************************************
// *********************** UIDeviceManager.h ************************   
/*******************************************************************/

#ifndef UI_DEVICE_MANAGER_H
#define UI_DEVICE_MANAGER_H

#include <string>
#include <vector>

#include "CommandHandler.h"
#include "UIDevice.h"
#include "XMLUtil.h"

using std::vector;
using std::string;

class UIDeviceManager : public ICommandCallback {
	public:
		UIDeviceManager();
		static void addUIDevice(ICommandCallback *parent, XMLParse params);
		void addUIDevice(XMLParse params);
		static void removeUIDevice(ICommandCallback *parent, XMLParse params);
		void removeUIDevice(XMLParse params);
		vector<UIDevice> getUIDevices();
		bool getUIDevice(string id, UIDevice *out);
		
	private:
		vector<UIDevice> allUIDevices;
		int getUIDeviceIndex(string id);
};

extern UIDeviceManager uiDeviceManager;

#endif /* UI_DEVICE_MANAGER_H */
