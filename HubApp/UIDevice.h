/********************************************************************
// *************************** UIDevice.h ***************************          
/*******************************************************************/

#ifndef UI_DEVICE_H
#define UI_DEVICE_H

#include <string>
#include <vector>

using std::vector;
using std::string;

class UIDevice {
	public:
		/** Constructor.
			*
			*@param id 			Device ID
			*@param type 		The device type
			*/
		UIDevice(string id, string name);
		void setName(string name);
		string getID();
		string getName();
	private:
		string uiDeviceID;
		string uiDeviceName;
};

#endif /* UI_DEVICE_H */