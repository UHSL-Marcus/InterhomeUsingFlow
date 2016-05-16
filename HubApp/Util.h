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
		/** Generate a UUID
			*
			* @param extra		String of extra information to add extra entropy (optional)
			* @return string 	String holding the UUID
			*/
		static string getUID(string extra = "");
		
		/** Get the current time in UTC
			*
			* @param format			Specify the format for the output datetime (optional)
			* @param modifySeconds 	Add or minus this amount of seconds from now. negative int subtracts, positive adds. (optional)
			* @return string 		Formatted UTC
			*/
		static string getUTC(string format = "%d/%m/%Y-%X", int modifySeconds = 0);
};

#endif /* UTIL_H */