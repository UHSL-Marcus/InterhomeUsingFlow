/********************************************************************
// ************************* HTTPRequest.h **************************          
/************************************ Author: Marcus Lee ***********/

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <curl/curl.h>
#include <string>
#include <cstring>
#include "Global.h"
#include "Util.h"

#include <iostream>

using std::string;
using std::stringstream;

using std::cout;

struct RecievedData {
  string dataString;
  size_t size;
};

class HTTPRequest {
	public:
		HTTPRequest();
		~HTTPRequest();
		static void globalSetup();
		static void globalCleanup();
		bool SOAPRequest(string soapBody, string action, string &out);
	private:
		CURL *curl;
		struct RecievedData data;
};




#endif /* HTTP_REQUEST_H */