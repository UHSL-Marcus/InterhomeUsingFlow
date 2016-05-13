/********************************************************************
// **************************** Util.cpp ****************************                  
/************************************ Author: Marcus Lee ***********/

#include "Util.h"

string Util::getUID(string extra) {
	hash<string> str_hash;
	stringstream ss;
	
	ss << extra << getUTC() << rand() % 100 + 1;
	size_t str_hash_out = str_hash(ss.str());
	ss.str(string());
	ss << str_hash_out;
	return ss.str();
}

string Util::getUTC(string format, int modifySeconds) {
	time_t t = time(0);
	struct tm now = *gmtime(&t); // UTC time, this is a must
	now.tm_sec += modifySeconds;
	timegm(&now);
	char timestampBuff[80];
	strftime(timestampBuff, sizeof(timestampBuff), format.c_str(), &now);
	
	return string(timestampBuff);
}