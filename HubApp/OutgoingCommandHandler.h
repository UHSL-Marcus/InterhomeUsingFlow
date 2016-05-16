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
		/** Send a command
			*
			*@param from 			ID of sending device
			*@param to				ID of reciving device
			*@param cmd				The command string
			*@param data			Extra data relating to the command (in an XML string)
			*@param protocols		List of the communication protocols to use, in order of priority
			*@param guid			The identifier of this message (optional)
			*/
		void sendCommand(string from, string to, string cmd, string data, vector<string> protocols, string guid = "");
	private:
	
};

extern OutgoingCommandHandler outgoingCommandHandler;

#endif /* OUTGOING_COMMAND_HANDLER_H */