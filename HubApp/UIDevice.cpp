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

void UIDevice::setCommunicationProtocols(vector<string> protocols) {
	communicationProtocols = protocols;
}

string UIDevice::getID() {
	return uiDeviceID;
}

string UIDevice::getName() {
	return uiDeviceName;
}

vector<string> UIDevice::getCommunicationProtocols() {
	return communicationProtocols;
}




/**** Private Functions ***/