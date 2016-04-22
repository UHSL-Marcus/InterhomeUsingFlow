/********************************************************************
// *************************** Device.cpp ***************************          
/*******************************************************************/


#include "UIDevice.h"

/**** Public Functions ***/

UIDevice::UIDevice(string id, string name) {
	uiDeviceID = id;
	uiDeviceName = name;
}

void UIDevice::setName(string name) {
	uiDeviceName = name;
}

string UIDevice::getID() {
	return uiDeviceID;
}

string UIDevice::getName() {
	return uiDeviceName;
}


/**** Private Functions ***/