/********************************************************************
// **************************** main.cpp ****************************
/*******************************************************************/

#include "CommandHandler_TEST.h"




Temp::Temp() {
	commandHandler.addCallback("cmd", Temp::callback, this);
}

void Temp::callback(ICommandCallback *parent, XMLParse params) {
	cout << "\ncallback called";
}

void Temp::add() {
	commandHandler.addCallback("cmd2", Temp::callback, this);
}

Temp temp;


void doCommandHandler_test() {
	
	
	
	XMLParse add1("<packet><data><room_name>room1</room_name></data></packet>");
	cout << "\nhandling command";
	commandHandler.handleCmd("cmd", add1);
	
	temp.add();

	cout << "\nhandling command2";
	commandHandler.handleCmd("cmd2", add1);	
	

	
}


