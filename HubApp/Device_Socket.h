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
		Device_Socket( string mac );
		bool changeStateValue(string name, string value);
		
	private:
		typedef Device super;
	
};

#endif /* DEVICE_SOCKET_H */