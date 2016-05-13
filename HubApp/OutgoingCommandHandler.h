/********************************************************************
// ********************* OutgoingCommandHandler.h *******************
/************************************ Author: Marcus Lee ***********/

#ifndef OUTGOING_COMMAND_HANDLER_H
#define OUTGOING_COMMAND_HANDLER_H

#include <string>
#include <vector>
#include <iostream>
#include "XMLUtil.h"
#include "MessageFormat.h"
#include "Util.h"

using std::string;
using std::vector;
using std::cout;


class OutgoingCommandHandler {
	public:
		OutgoingCommandHandler();
		void sendCommand(string from, string to, string cmd, string data, vector<string> protocols, string guid = "");
	private:
	
};

extern OutgoingCommandHandler outgoingCommandHandler;

#endif /* OUTGOING_COMMAND_HANDLER_H */