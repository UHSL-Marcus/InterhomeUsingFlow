/********************************************************************
// *********************** CommandHandler.cpp ***********************
/*******************************************************************/

#include "CommandHandler.h"

using namespace std;

CommandHandler::CommandHandler() {
	bindingCount = 0;
}

bool CommandHandler::addCallback(char * cmd, CommandCallbackFunction callback) {
	bool success = false;
	
	if (bindingCount < MAX_CALLBACKS) {
		strcpy(callbacks[bindingCount].command, cmd);
		callbacks[bindingCount].callback = callback;
		bindingCount++;
		success = true;
	}
	
	return success;
	
}

bool CommandHandler::updateCallack(char * cmd, CommandCallbackFunction callback) {
	bool success = false;
	
	CommandBinding bind = findBinding(cmd);
	if (bind != null) {
		bind.callback = callback;
		success = true;
	}
	return success;
}

bool CommandHandler::handleCmd(char * cmd) {
	success = false
	
	CommandBinding bind = findBinding(cmd)
	if (bind != NULL) {
		callbacks[i].callback();
			
		success = true;
	}
			
	return success;
}

CommandBinding findBinding(char * cmd) {
	
	for (int i = 0; i < bindingCount; i++) {
		size_t cmdLen = strlen(callbacks[i].command);
		if (strncmp(cmd, callbacks[i].command, cmdLen) == 0 && strlen(cmd) == cmdLen) {
			return callbacks[i];
		}
	}
	return NULL;
}

CommandHandler commandHandler;
