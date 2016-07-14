
#include <algorithm>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/c14n.h>
#include <libxml/xpathInternals.h>
#include <openssl/sha.h>
#include <openssl/buffer.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

using std::string;
using std::cout;

static const char *document = 	"<doc xmlns:u=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\">"
									"<u:Timestamp u:Id=\"_0\">"
										"<u:Created>2016-05-10T09:05:59.307Z</u:Created>"
										"<u:Expires>2016-05-10T09:10:59.307Z</u:Expires>"
									"</u:Timestamp>"
								"</doc>";
								

string Base64Encode(unsigned char* buffer, size_t length) { //Encodes a binary safe base 64 string
	BIO *mem, *b64;
	BUF_MEM *bufferPtr;

	b64 = BIO_new(BIO_f_base64());
	mem = BIO_new(BIO_s_mem());
	mem = BIO_push(b64, mem);

	BIO_set_flags(mem, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
	BIO_write(mem, buffer, length);
	BIO_flush(mem);
	BIO_get_mem_ptr(mem, &bufferPtr);
	BIO_set_close(mem, BIO_NOCLOSE);
	string out(bufferPtr->data);
	BIO_free_all(mem);
	
	out = out.substr(0, out.find_last_of('=')+1);
	return out;
}


size_t Base64DecodeLen(const char* b64) {
	size_t length = strlen(b64);
	size_t padding = length - string(b64).find_first_of('=');
	cout << "\n PADDING: " << padding;
	
	return (length*3)/4 - padding;
	
}
int Base64Decode(char* b64message, unsigned char** buffer, size_t* length) { //Decodes a base64 encoded string
	BIO *mem, *b64;

	size_t decodeLen = Base64DecodeLen(b64message);
	cout << "\n DECODE LEN: " << decodeLen;
	*buffer = (unsigned char*)malloc(decodeLen + 1);
	(*buffer)[decodeLen] = '\0';

	mem = BIO_new_mem_buf(b64message, -1);
	b64 = BIO_new(BIO_f_base64());
	mem = BIO_push(b64, mem);

	BIO_set_flags(mem, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
	*length = BIO_read(mem, *buffer, strlen(b64message));
	cout << "\n len: " << *length << ", decodeLen: " << decodeLen;
	BIO_free_all(mem);

	return (0); //success
}

string GetHexRepresentation(const unsigned char * bytes, size_t length)
{
    std::stringstream ss;
	for(int i=0; i<length; ++i)
		ss << std::hex << (int)bytes[i];
	return ss.str();
}
							
int main(void) {
	
	LIBXML_TEST_VERSION
	
	xmlDocPtr doc;
	//doc = xmlReadMemory(document, strlen(document), "noname.xml", NULL, 0);
	doc = xmlReadFile("testXML.xml", NULL, 0);
	
	if (doc != NULL) {
		cout << "\n Doc read";
		
		xmlNodeSetPtr nodeset;
		xmlChar *xpath = (xmlChar*) "//u:Timestamp[@u:Id=\"_0\"]/descendant-or-self::node() | //u:Timestamp[@u:Id=\"_0\"]/descendant-or-self::node()/attribute::* | //u:Timestamp[@u:Id=\"_0\"]/descendant-or-self::node()/namespace::*";
		
		xmlXPathContextPtr context = xmlXPathNewContext(doc);
		xmlXPathRegisterNs(context, (xmlChar*)"u",(xmlChar*) "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd");
		xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(xpath, context);
		xmlXPathFreeContext(context);
		
		if(xpathObj != NULL) {
			if(!xmlXPathNodeSetIsEmpty(xpathObj->nodesetval)) {
				cout << "\nTimestamp selected";
				nodeset = xpathObj->nodesetval;
				cout << "\ncount: " << nodeset->nodeNr;
				xmlChar* inclusive_ns[] = {(xmlChar*)"xmlns:u=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\"", NULL};
		
				xmlChar *out;
				if (xmlC14NDocDumpMemory(doc, nodeset, XML_C14N_EXCLUSIVE_1_0, inclusive_ns, 1, &out) > 0) {
					 cout << "\nXML Canonicalized: \n" << out;
					 
					 const xmlChar* hashIn = out;
					 
					 unsigned char mdOut[SHA_DIGEST_LENGTH];
					 unsigned char * sha1Hash = SHA1(hashIn, xmlStrlen(hashIn), mdOut);
					 string base64EncodeOutput = Base64Encode(mdOut, SHA_DIGEST_LENGTH);
					 
					 cout << "\n Base64 encoded SHA1 of Timestamp: " << base64EncodeOutput;
					 cout << "\n refrence encoding: uDP0k/JY3/JMjmYCpPT/DS1VrbY=";
				}
			}
		}
		
		cout << "\nSignedInfo Section";
		xmlChar *xpath2 = (xmlChar*) "//default:SignedInfo/descendant-or-self::node() | //default:SignedInfo/descendant-or-self::node()/attribute::* | //default:SignedInfo/descendant-or-self::node()/namespace::*";
		
		xmlNodeSetPtr nodeset2;
		xmlXPathContextPtr context2 = xmlXPathNewContext(doc);
		xmlXPathRegisterNs(context2, (xmlChar*)"default",(xmlChar*) "http://www.w3.org/2000/09/xmldsig#");
		xmlXPathObjectPtr xpathObj2 = xmlXPathEvalExpression(xpath2, context2);
		xmlXPathFreeContext(context2);
		
		if(xpathObj != NULL) {
			if(!xmlXPathNodeSetIsEmpty(xpathObj2->nodesetval)) {
				cout << "\nSignedInfo selected";
				nodeset2 = xpathObj2->nodesetval;
				cout << "\ncount: " << nodeset2->nodeNr;
				
				xmlChar *out2;
				if (xmlC14NDocDumpMemory(doc, nodeset2, XML_C14N_EXCLUSIVE_1_0, NULL, 1, &out2) > 0) {
					cout << "\nXML Canonicalized: \n" << out2;

					const xmlChar* hashIn2 = out2;
					
					unsigned char* decodedKey1;
					size_t length1;
					Base64Decode("oTZ50h+KLnRVxBR8HcL3fn9hpZFBhbBueo4DSQDmMYI=", &decodedKey1, &length1);
					unsigned char* decodedKey2;
					size_t length2;
					Base64Decode("Nz6kpJfuGr37xFpEuw4w/AZn36d0EGBsC8vZHRX2Vq8=", &decodedKey2, &length2);
					
					unsigned char longKey[length1+length2] = "";
					strcpy((char*)longKey, (char*)decodedKey1);
					strcat((char*)longKey, (char*)decodedKey2);
					
					unsigned char mdOut2[SHA_DIGEST_LENGTH];
					unsigned int* md_len;

					/*HMAC_CTX ctx;
					HMAC_CTX_init(&ctx);

					HMAC_Init_ex(&ctx, key, strlen(key), EVP_sha1(), NULL);
					HMAC_Update(&ctx, hashIn2, xmlStrlen(hashIn2));
					HMAC_Final(&ctx, mdOut2, NULL);
					HMAC_CTX_cleanup(&ctx);*/
					
					//cout << "\nmdOut2: " << GetHexRepresentation(mdOut2, SHA_DIGEST_LENGTH);

					unsigned char * hmacSha1Hash = HMAC(EVP_sha1(), longKey, length1+length2, out2, xmlStrlen(out2), NULL, NULL);
					//cout << "\nhmacSha1Hash: " << GetHexRepresentation(hmacSha1Hash, SHA_DIGEST_LENGTH);
					
					string base64EncodeOutput2 = Base64Encode(hmacSha1Hash, SHA_DIGEST_LENGTH);

					cout << "\n Base64 encoded SHA1 of SignedInfo: " << base64EncodeOutput2;
					cout << "\n refrence encoding: YZGgyFRrUinhPoLbH8qd9bUomUI=";
				}
			}
		}
		
		
	}
	
	
	/*const unsigned char input[] = 	"<u:Timestamp xmlns:u=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\" u:Id=\"_0\">"
										"<u:Created>2016-05-10T09:05:59.307Z</u:Created>"
										"<u:Expires>2016-05-10T09:10:59.307Z</u:Expires>"
									"</u:Timestamp>";
	unsigned char mdOut[SHA_DIGEST_LENGTH];
	unsigned char mdOut2[SHA_DIGEST_LENGTH];
	
	unsigned char * sha1Hash = SHA1(input, strlen((char*)input), mdOut2);
	
	SHA_CTX context;
    SHA1_Init(&context);
    SHA1_Update(&context, input, strlen((char*)input));
	SHA1_Final(mdOut, &context);

	cout << "\nsha1Hash: " << GetHexRepresentation(sha1Hash, SHA_DIGEST_LENGTH);
	//cout << "\nmdOut: " << GetHexRepresentation(mdOut, SHA_DIGEST_LENGTH);

	unsigned char text[]="any carnal pleasure";

	string base64EncodeOutput = Base64Encode(sha1Hash, SHA_DIGEST_LENGTH);
	cout << "\nb64 encode: " << base64EncodeOutput;

	unsigned char *base64decode;
	size_t len;
	Base64Decode("uDP0k/JY3/JMjmYCpPT/DS1VrbY=", &base64decode, &len, SHA_DIGEST_LENGTH);
	cout << "\nrefrence b64 encode: " << "uDP0k/JY3/JMjmYCpPT/DS1VrbY=";
	cout << "\nrefrence SHA1 digest: " << GetHexRepresentation(base64decode, SHA_DIGEST_LENGTH);
	

	/*cout << "\nbase64 'any carnal pleasure': " << Base64Encode(text, strlen((char*)text));
	
	unsigned char base64decode;
	size_t len;
	Base64Decode((char*)Base64Encode(text, strlen((char*)text)).c_str(), &base64decode, &len, strlen((char*)text));
	
	cout << "\ndecoded b64: " << base64decode;
	
	Base64Decode((char*)base64EncodeOutput.c_str(), &base64decode, &len, SHA_DIGEST_LENGTH);
	cout << "\nsha1Hash b64decode: " << GetHexRepresentation(base64decode, SHA_DIGEST_LENGTH);*/
	
	cout << "\n\nEnd\n\n";
	xmlCleanupParser();
	
	return 0;
}