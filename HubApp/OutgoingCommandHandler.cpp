/********************************************************************
// ******************* OutgoingCommandHandler.cpp *******************
/*******************************************************************/

#include "OutgoingCommandHandler.h"

OutgoingCommandHandler::OutgoingCommandHandler() {
	
}

void OutgoingCommandHandler::sendCommand(string from, string to, string cmd, string data, vector<string> protocols, string guid) {
	
	XMLBuild messageXML(M_ROOT);
	
	messageXML.addStringNode(M_SENDER_PATH, from);
	messageXML.addStringNode(M_RECIPTIENT_PATH, to);
	messageXML.addStringNode(M_TYPE_PATH, cmd);
	
	time_t t = time(0);
	struct tm now = *gmtime(&t); // UTC time, this is a must
	char timestampBuff[80];
	strftime(timestampBuff, sizeof(timestampBuff), "%d/%m/%Y-%X", &now);
	messageXML.addStringNode(M_TIMESTAMP_PATH, timestampBuff);
	
	if (guid == "") {
		hash<string> str_hash;
		stringstream ss;
		ss << from << timestampBuff << rand() % 100 + 1;
		size_t str_hash_out = str_hash(ss.str());
		ss.str(string());
		ss << str_hash_out;
		guid = ss.str();
	}
	messageXML.addStringNode(M_GUID_PATH, guid);
	
	if (!messageXML.addXML(M_DATA_PATH, data)) {
		messageXML.removeNode(M_DATA_PATH);
		messageXML.addStringNode(M_DATA_PATH, data);
	}
	
	string messageString = messageXML.getXML();
	
	// do following in new thread
	// loop through protocols break once first one sends. 
	// depending on how the protocol works. ack could be built in to it (FLOW for example) or may have to wait for manual ack using the Commandhandler
	// need to see how callbacks will work from different threads. 
	
	
	cout << "\n\n ---OUTGOING---\n" << messageString;
	

}

OutgoingCommandHandler outgoingCommandHandler;