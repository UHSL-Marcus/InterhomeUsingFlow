/********************************************************************
// ************************ HTTPRequest.cpp *************************          
/************************************ Author: Marcus Lee ***********/

#include "HTTPRequest.h"

#include <iostream>


void HTTPRequest::globalSetup() {
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

void HTTPRequest::globalCleanup() {
	curl_global_cleanup();
}


HTTPRequest::HTTPRequest() {
	curl = curl_easy_init();
}

HTTPRequest::~HTTPRequest() {
	curl_easy_cleanup(curl);
}


static size_t recievedDataCallback(void *contents, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize = size * nmemb;

	struct RecievedData *data = (struct RecievedData *)userdata;
	
	stringstream ssData;
	ssData << data->dataString << (char*)contents;
	data->dataString = ssData.str();
	data->size += realsize;

	return realsize;
}
bool HTTPRequest::SOAPRequest(string soapBody, string action, string &out) {
	
	//std::cout   << "\nNew SOAPRequest";
	bool success = false;
	stringstream errors;
	
	stringstream xmlSS;
	string messageID = Util::getUID(soapBody);
	
	xmlSS << 	"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://www.w3.org/2005/08/addressing\" xmlns:u=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\">"
					"<s:Header>"
						"<a:Action s:mustUnderstand=\"1\">http://tempuri.org/ISmartSocketsWebService/" << action << "</a:Action>"
						"<a:MessageID>" << messageID << "</a:MessageID>"
						"<a:ReplyTo>"
							"<a:Address>http://www.w3.org/2005/08/addressing/anonymous</a:Address>"
						"</a:ReplyTo>"
						"<a:To s:mustUnderstand=\"1\">https://mmtsnap.mmt.herts.ac.uk/sssvc/ServiceImplimentation/Start.svc</a:To>"
						"<o:Security s:mustUnderstand=\"1\" xmlns:o=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd\">"
							"<u:Timestamp u:Id=\"_0\">"
								"<u:Created>" << Util::getUTC("%Y-%m-%dT%X.000Z") << "</u:Created>"
								"<u:Expires>" << Util::getUTC("%Y-%m-%dT%X.000Z", 5*60) << "</u:Expires>"
							"</u:Timestamp>"
							"<o:UsernameToken u:Id=\"" << Util::getUID(Global::webServiceUsr) << "\">"
								"<o:Username>" << Global::webServiceUsr << "</o:Username>"
								"<o:Password o:Type=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText\">" << Global::webServicePwd << "</o:Password>"
							"</o:UsernameToken>"
						"</o:Security>"
					"</s:Header>"
					"<s:Body>" << soapBody << "</s:Body>"
				"</s:Envelope>";
			
	const string &temp = xmlSS.str();
	const char* xml = temp.c_str();
	
	//std::cout   << "\nRequest XML: \n" << temp;
	
	if(curl) {
		//std::cout   << "\nnew curl";
		curl_easy_reset(curl);
		
		curl_easy_setopt(curl, CURLOPT_URL, "https://mmtsnap.mmt.herts.ac.uk/sssvc/ServiceImplimentation/Start.svc");
		//curl_easy_setopt(curl, CURLOPT_URL, "https://147.197.205.57/ServiceImplimentation/Start.svc");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xml);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
		
		struct curl_slist *list = NULL;
		
		list = curl_slist_append(list, "Connection: Keep-Alive");
		list = curl_slist_append(list, "Content-Type: application/soap+xml; charset=utf-8");
		//list = curl_slist_append(list, "Host: 147.197.205.57");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, recievedDataCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&data);
		
		//std::cout   << "\nSet curl options";
		
		CURLcode response = curl_easy_perform(curl);
		
		//std::cout   << "\nmade request";
		
		//std::cout   << "\ncurl response code: " << response;
		
		if(response == CURLE_OK) {
			//std::cout   << "\nOK response";
			size_t found = data.dataString.find("200 OK");
			if (found != string::npos) {
				//std::cout   << "\n200 Code";
				found = data.dataString.find("<s:Envelope");
				if (found != string::npos) {
					//std::cout   << "\nSOAP envelope found";
					string envelope = data.dataString.substr(found, string::npos);
					
					XMLParse xml(envelope);
					string responseMessageID;
					try
					{
						xml.getStringNode("//*[local-name()='RelatesTo']", &responseMessageID);
						
						if (responseMessageID.compare(messageID) == 0) {
							//std::cout   << "\nMessageID matches";
							out = data.dataString.substr(found, string::npos);
							success = true;
							
							//std::cout  << "\nresponse:\n" << out;  
						} errors << "\nMessage RelatesTo ID does not match. Response: " << data.dataString;
					}
					catch (const pugi::xpath_exception& e)
					{
						//std::cout  << "\nException: " << e.what();
					}
					
				} else errors << "\nNo SOAP Envelope. Response: " << data.dataString;
			} else errors << "\nHTTP Response not '200 OK'. Response: " << data.dataString;
			
		} else errors << "\nCurl response not 'OK': " << curl_easy_strerror(response);
	} else errors << "\nCurl failed to initialise";
	
	if (!success)
		out = errors.str();
	
	return success;
}

