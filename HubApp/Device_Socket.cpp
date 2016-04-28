/********************************************************************
// *********************** Device_Socket.cpp ***********************          
/*******************************************************************/

#include "Device_Socket.h"

Device_Socket::Device_Socket( string mac ) : super(mac, TYPE, SOCKET_STATE_LIST) {
	
}

bool Device_Socket::changeStateValue(string name, string value) {
	super::changeStateValue(name, "(socket)"+value);
}