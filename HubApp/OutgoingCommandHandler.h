/********************************************************************
// ********************* OutgoingCommandHandler.h *******************
/************************************ Author: Marcus Lee ***********/

#ifndef OUTGOING_COMMAND_HANDLER_H
#define OUTGOING_COMMAND_HANDLER_H

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>
#include "XMLUtil.h"
#include "MessageFormat.h"

using std::string;
using std::vector;
using std::time;
using std::hash;
using std::stringstream;
using std::cout;


class OutgoingCommandHandler {
	public:
		OutgoingCommandHandler();
		void sendCommand(string from, string to, string cmd, string data, vector<string> protocols, string guid = "");
	private:
	
};

extern OutgoingCommandHandler outgoingCommandHandler;

#endif /* OUTGOING_COMMAND_HANDLER_H */