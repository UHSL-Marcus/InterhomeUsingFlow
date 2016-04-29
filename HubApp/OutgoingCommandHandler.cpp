/********************************************************************
// ******************* OutgoingCommandHandler.cpp *******************
/*******************************************************************/

#include "OutgoingCommandHandler.h"

OutgoingCommandHandler::OutgoingCommandHandler() {
	
}

bool OutgoingCommandHandler::sendCommand(string from, string to, string cmd, string data, vector<string> protocols, string guid = "") {
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
		ss << from << timestampBuff << rand() % 100 + 1
		size_t str_hash_out = str_hash(ss..str());
		ss.str(string());
		ss << str_hash_out;
		guid = ss.str();
	}
	messageXML.addStringNode(M_GUID_PATH, guid);
	messageXML.addStringNode(M_DATA_PATH, guid);
	
	
}