/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "HTTPRequest_TEST.h"

namespace HTTPRequest_TEST {
	
	
	
	
}
using namespace HTTPRequest_TEST;


void doHTTPRequest_test() {
	
	HTTPRequest::globalSetup();
	
	HTTPRequest req;
	cout << "\n******SENDING REQUEST**********\n";
	cout << "\nBody: <GetAllDevices xmlns=\"http://tempuri.org/\"/>";
	
	string response = "No Response recieved";
	if (req.SOAPRequest("<GetAllDevices xmlns=\"http://tempuri.org/\"/>", "GetAllDevices", response)) {
		cout << "\nResponse: \n" << response;
	}
	else 
		cout << "\nRequest Failed: " << response;
	
	
	
	HTTPRequest::globalCleanup();
	
	
	
}