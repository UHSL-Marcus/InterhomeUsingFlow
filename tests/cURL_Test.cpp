
#include <cstring>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>

using std::string;
using std::cout;

char * xml = 	"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://www.w3.org/2005/08/addressing\" xmlns:u=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\">"
					"<s:Header>"
						"<a:Action s:mustUnderstand=\"1\">http://tempuri.org/ISmartSocketsWebService/GetAllDevices</a:Action>"
						"<a:MessageID>urn:uuid:cf03f1f1-1e2a-4d71-2-4c9aa335ad69</a:MessageID>"
						"<a:ReplyTo>"
							"<a:Address>http://www.w3.org/2005/08/addressing/anonymous</a:Address>"
						"</a:ReplyTo>"
						"<a:To s:mustUnderstand=\"1\">https://ent-ml15aaf-1.herts.ac.uk/ServiceImplimentation/Start.svc</a:To>"
						"<o:Security s:mustUnderstand=\"1\" xmlns:o=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd\">"
							"<u:Timestamp u:Id=\"_0\">"
								"<u:Created>2016-05-13T08:03:18.016Z</u:Created>"
								"<u:Expires>2016-05-13T11:03:18.016Z</u:Expires>"
							"</u:Timestamp>"
							"<o:UsernameToken u:Id=\"uuid-6df7fed1-2-4a3a-8df3-505e2277bda9-1\">"
								"<o:Username>root</o:Username>"
								"<o:Password o:Type=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText\">root</o:Password>"
							"</o:UsernameToken>"
						"</o:Security>"
					"</s:Header>"
					"<s:Body>"
						"<GetAllDevices xmlns=\"http://tempuri.org/\"/>"
					"</s:Body>"
				"</s:Envelope>";

struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;

  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  

  return realsize;
}

int main(void) {
	
	CURL *curl;
	CURLcode response;
	
	curl_global_init(CURL_GLOBAL_DEFAULT);
	
	curl = curl_easy_init();
	
	FILE *filep = fopen("dump", "wb");
	
	struct curl_slist *list = NULL;
	
	struct MemoryStruct chunk;
 
	chunk.memory = (char*) malloc(1);  /* will be grown as needed by the realloc above */ 
	chunk.size = 0;    /* no data at this point */ 
	
	if(curl) {
		
		curl_easy_setopt(curl, CURLOPT_STDERR, filep);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		
		curl_easy_setopt(curl, CURLOPT_URL, "https://147.197.205.57/ServiceImplimentation/Start.svc");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xml);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		
		list = curl_slist_append(list, "Connection: Keep-Alive");
		list = curl_slist_append(list, "Content-Type: application/soap+xml; charset=utf-8");
		//list = curl_slist_append(list, "Host: 147.197.205.57");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		
		
		response =  curl_easy_perform(curl);
		if(response != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(response));
		else {
			/*
			 * Now, our chunk.memory points to a memory block that is chunk.size
			 * bytes big and contains the remote file.
			 *
			 * Do something nice with it!
			 */ 
		 
			printf("%lu bytes retrieved\n", (long)chunk.size);
			printf("\n%s\n\n", chunk.memory);
		}
		
		cout << "\ndone";
		curl_easy_cleanup(curl);
	}
	
	curl_global_cleanup();
	 
	cout << "\n";
	return 0;
}