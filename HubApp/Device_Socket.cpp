/********************************************************************
// *********************** Device_Socket.cpp ***********************          
/************************************ Author: Marcus Lee ***********/

#include "Device_Socket.h"

Device_Socket::Device_Socket( string mac ) : super(mac, DEVICE_TYPE, SOCKET_STATE_LIST) {
	
}

bool Device_Socket::changeStateValue(string name, string value) {
	super::changeStateValue(name, "(socket)"+value);
}