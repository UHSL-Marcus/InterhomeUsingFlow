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
#include "XMLUtil.h"

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
		/** Constructor.
			*
			*/
		HTTPRequest();
		~HTTPRequest();
		/** Initalise the global enviroment for cURL. Only call once and before the program is threaded. 
			*
			*/
		static void globalSetup();
		
		/** Clean the global enviroment for cURL. Only call once and after the programs threads have all joined. 
			*
			*/
		static void globalCleanup();
		
		/** Execute a SOAP Request to the webservice
			*
			*@param soapBody 	The XML string holding the body of the soap request
			*@param action		The name of the action being requested
			*@param &out		Refrence to a string to hold the response XML from the server
			*
			*@return bool 		Request successful
			*/
		bool SOAPRequest(string soapBody, string action, string &out);
	private:
		CURL *curl;
		struct RecievedData data;
};




#endif /* HTTP_REQUEST_H */