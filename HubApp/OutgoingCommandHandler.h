/********************************************************************
// ********************* OutgoingCommandHandler.h *******************
/*******************************************************************/

#ifndef OUTGOING_COMMAND_HANDLER_H
#define OUTGOING_COMMAND_HANDLER_H

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include "XMLUtil.h"
#include "MessageFormat.h"

using std::string;
using std::vector;
using std::time;
using std::hash;
using std::stringstream;


class OutgoingCommandHandler {
	public:
		OutgoingCommandHandler();
		bool sendCommand(string from, string to, string cmd, string data, vector<string> protocols, string guid = "");
	private:
	
};

extern OutgoingCommandHandler outgoingCommandHandler;

#endif /* OUTGOING_COMMAND_HANDLER_H */