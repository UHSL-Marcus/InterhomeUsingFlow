/********************************************************************
// ************************* Device_Socket.h ************************          
/************************************ Author: Marcus Lee ***********/


#ifndef DEVICE_SOCKET_H
#define DEVICE_SOCKET_H

#define DEVICE_TYPE "device_socket"

#include "Device.h"

#include <string>

using std::string;

class Device_Socket : public Device {
	
	public:
		/** Constructor. This class should not be inialised directly, only ever via a child
			*
			*@param mac 			Device MAC Address
			*/
		Device_Socket( string mac );
		
		/** Change a state value on this device
			*
			*@param string 	Field name
			*@param	string	New value
			*@return bool 	state value successfully changed
			*/
		bool changeStateValue(string name, string value);
		
	private:
		typedef Device super;
	
};

#endif /* DEVICE_SOCKET_H */