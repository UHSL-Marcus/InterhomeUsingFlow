/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "CommandHandler_TEST.h"




Temp::Temp() {
	
}

void Temp::callback(ICommandCallback *parent, XMLParse params) {
	cout << "\ncallback called\n";
}

void Temp::add() {
	commandHandler.addCallback("cmd", Temp::callback, this);
}

Temp temp;


void doCommandHandler_test() {
	
	
	
	XMLParse add1("<packet><data><room_name>room1</room_name></data></packet>");
	
	cout << "\nadding command binding";
	temp.add();
	
	cout << "\nhandling command";
	commandHandler.handleCmd("cmd", add1);
	
	

	

	
}


