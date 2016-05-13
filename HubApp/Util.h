/********************************************************************
// ***************************** Util.h *****************************                  
/************************************ Author: Marcus Lee ***********/

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <ctime>

using std::string;
using std::time;
using std::hash;
using std::stringstream;


class Util {
	public:
		static string getUID(string extra = "");
		static string getUTC(string format = "%d/%m/%Y-%X", int modifySeconds = 0);
};

#endif /* UTIL_H */