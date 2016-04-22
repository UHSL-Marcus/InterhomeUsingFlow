/********************************************************************
// *********************** CommandHandler.cpp ***********************
/*******************************************************************/

#include "CommandHandler.h"
#include <iostream>

using std::cout;

/**** Public Functions ***/

CommandHandler::CommandHandler() {}

bool CommandHandler::addCallback(string cmd, CommandCallbackFunction callback, ICommandCallback *parent) {
	
	cout << " \n Adding command: " << cmd;
	cout << " :: binding count: " << callbacks.size();
	bool success = false;
	
	CommandBinding temp;
	temp.command = cmd;
	temp.callback = callback;
	temp.parent = parent;
	callbacks.push_back(temp);
	success = true;
	
	cout << " :: binding count: " << callbacks.size();
	
	return success;
}

bool CommandHandler::updateCallack(string cmd, CommandCallbackFunction callback, ICommandCallback *parent) {
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

bool CommandHandler::handleCmd(string cmd, XMLParse params) {
	
	cout << " \n handling command: " << cmd;

	cout << " :: binding count: " << callbacks.size();
	bool success = false;
	
	vector<CommandBinding> bindings = findBindings(cmd);
	cout << " :: find bindings";
	if (!bindings.empty()) {
		cout << " :: bindings not empty";
		for (int i = 0; i < bindings.size(); i++) {
			cout << " :: callback";
			bindings[i].callback(bindings[i].parent, params);
		}
		
		success = true;
	}
			
	return success;
}

/**** Private Functions ***/

vector<CommandBinding> CommandHandler::findBindings(string cmd, ICommandCallback *parent) {
	vector <CommandBinding> bindings; 
	
	for (int i = 0; i < callbacks.size(); i++) {
		if (callbacks[i].parent == parent && cmd == callbacks[i].command && cmd.size() == callbacks[i].command.size()) {
			bindings.push_back(callbacks[i]);
		}
	}
	
	return bindings;
}

vector<CommandBinding> CommandHandler::findBindings(string cmd) {
	vector <CommandBinding> bindings; 
	cout << " \n finding bindings";
	cout << " :: binding count: " << callbacks.size();
	for (int i = 0; i < callbacks.size(); i++) {
		cout << " :: binding cmd: " << callbacks[i].command;
		if (cmd == callbacks[i].command && cmd.size() == callbacks[i].command.size()) {
			cout << " :: added";
			bindings.push_back(callbacks[i]);
		}
	}
	
	return bindings;
}

CommandHandler commandHandler;
