/********************************************************************
// *************************** UIDevice.h ***************************          
/************************************ Author: Marcus Lee ***********/

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
		
		/** Set the name of this UI device
			*
			*@param name 	The new name
			*/
		void setName(string name);
		
		/** Set the communication protocols available for this UI device
			*
			*@param protocols 	List of communication protocols
			*/
		void setCommunicationProtocols(vector<string> protocols);
		
		/** Get the ID of this UI device
			*
			*@return string 	UI Device ID
			*/
		string getID();
		
		/** Get the Name of this UI device
			*
			*@return string 	UI Device Name
			*/
		string getName();
		
		/** Get a list of the communication protocols available for this UI device
			*
			*@return vector<string> 	List of available communication protocols
			*/
		vector<string> getCommunicationProtocols();
	private:
		string uiDeviceID;
		string uiDeviceName;
		vector<string> communicationProtocols;
};

#endif /* UI_DEVICE_H */