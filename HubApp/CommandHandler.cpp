/********************************************************************
// *********************** CommandHandler.cpp ***********************
/*******************************************************************/

#include "CommandHandler.h"

#include <iostream>

CommandHandler::CommandHandler() {
	
}

bool CommandHandler::addCallback(char * cmd, CommandCallbackFunction callback, ICommandCallback *parent) {
	
	bool success = false;
	
	CommandBinding temp;
	strcpy(temp.command, cmd);
	temp.callback = callback;
	temp.parent = parent;
	callbacks.push_back(temp);
	success = true;
	
	return success;
}

bool CommandHandler::updateCallack(char * cmd, CommandCallbackFunction callback, ICommandCallback *parent) {
	bool success = false;
	
	vector<CommandBinding> bindings = findBindings(cmd);
	if (!bindings.empty()) {
		for (int i = 0; i < bindings.size(); i++) {
			bindings[i].callback = callback;
		}
		success = true;
	}
	return success;
}

bool CommandHandler::handleCmd(char * cmd) {
	bool success = false;
	
	vector<CommandBinding> bindings = findBindings(cmd);
	if (!bindings.empty()) {
		for (int i = 0; i < bindings.size(); i++) {
			bindings[i].callback(bindings[i].parent);
		}
			
		success = true;
	}
			
	return success;
}

vector<CommandBinding> CommandHandler::findBindings(char * cmd, ICommandCallback *parent) {
	vector <CommandBinding> bindings; 
	
	for (int i = 0; i < callbacks.size(); i++) {
		size_t cmdLen = strlen(callbacks[i].command);
		if (callbacks[i].parent == parent && strncmp(cmd, callbacks[i].command, cmdLen) == 0 && strlen(cmd) == cmdLen) {
			bindings.push_back(callbacks[i]);
		}
	}
	
	return bindings;
}

vector<CommandBinding> CommandHandler::findBindings(char * cmd) {
	vector <CommandBinding> bindings; 
	
	for (int i = 0; i < callbacks.size(); i++) {
		size_t cmdLen = strlen(callbacks[i].command);
		if (strncmp(cmd, callbacks[i].command, cmdLen) == 0 && strlen(cmd) == cmdLen) {
			bindings.push_back(callbacks[i]);
		}
	}
	
	return bindings;
}

CommandHandler commandHandler;
