/********************************************************************
// ************************ RoomManager.cpp *************************   
/************************************ Author: Marcus Lee ***********/



#include "RoomManager.h"

/**** Public Functions ***/

RoomManager::RoomManager() {

}

void RoomManager::setCommandCallbacks() {
	commandHandler.addCallback("AddNewRoom", RoomManager::addNewRoom, this);
	commandHandler.addCallback("RemoveRoom", RoomManager::removeRoom, this);
	commandHandler.addCallback("UpdateRoom", RoomManager::updateRoom, this);
}

void RoomManager::addNewRoom(ICommandCallback *parent, XMLParse params) {
	(static_cast<RoomManager*>(parent))->addNewRoom(params);
}
void RoomManager::addNewRoom(XMLParse params) {

	bool success = false;
	
	string name;
	if (params.getStringNode(M_ROOM_NAME_PATH, &name)) {
		
		// Add new room to the database and get the ID back
		XMLBuild body("SetNewRoom");
		body.addAttribute("SetNewRoom", "xmlns", "http://tempuri.org/");
		body.addStringNode("SetNewRoom/room/b:PropertyID", Global::propertyID);
		body.addStringNode("SetNewRoom/room/b:RoomName", name);
		body.addAttribute("SetNewRoom/room", "xmlns:b", "http://schemas.datacontract.org/2004/07/SmartSocketsWebService");
		body.addAttribute("SetNewRoom/room", "xmlns:i", "http://www.w3.org/2001/XMLSchema-instance");
		
		HTTPRequest req;
		string response;
		req.SOAPRequest(body.getXML(), "SetNewRoom", response);
		
		XMLParse reply(response);
		
		string requestOutcome;
		if (reply.getStringNode("//SetNewRoomResult", &requestOutcome)) {
			if (requestOutcome.compare("true") == 0) {
				
				string id;
				if (reply.getStringNode("//ID", &id)) {
					
					try {
						std::stoi(id, NULL, 10); // just testing the ID to make sure it is an int
						
						Room room(id, name); // temp
				
						int idx = getRoomIndex(name);
						if (idx < 0) {
							allRooms.push_back(room);
							success = true;
						}
					}
					catch (exception& e) {
						
					}
					
				}
			}
		}
	}
	
	
	// send success to UI device 
	string uiID;
	string guid;
	if (params.getStringNode(M_SENDER_PATH, &uiID) && params.getStringNode(M_GUID_PATH, &guid)) {
		uiDeviceManager.uiDeviceBool(uiID, success, guid);
	}
}

vector<Room> RoomManager::getRooms() {
	return allRooms;
}

bool RoomManager::getRoom(string id, Room *out) {

	int idx = getRoomIndex(id);
	if (idx > -1) {
		*out = allRooms[idx];
		return true;
	}

	return false;
}

void RoomManager::removeRoom(ICommandCallback *parent, XMLParse params) {
	(static_cast<RoomManager*>(parent))->removeRoom(params);
}
void RoomManager::removeRoom(XMLParse params) {
	bool success = false;
	
	string id;
	if (params.getStringNode(M_ROOM_ID_PATH, &id)) {
		
		int idx = getRoomIndex(id);
		if (idx > -1) {
			// remove room from database
			XMLBuild body("RemoveRoom");
			body.addAttribute("RemoveRoom", "xmlns", "http://tempuri.org/");
			body.addStringNode("RemoveRoom/ID", id);
			
			HTTPRequest req;
			string response;
			req.SOAPRequest(body.getXML(), "RemoveRoom", response);
			
			XMLParse reply(response);
			
			string requestOutcome;
			if (reply.getStringNode("//RemoveRoomResult", &requestOutcome)) {
				if (requestOutcome.compare("true") == 0) {
					allRooms.erase(allRooms.begin()+idx);
					success = true;
					// send new room configuration to UI or upon recieveing the bool it can request it?
				}
			}
			
		}
	}
	
	// send success to UI device 
	string uiID;
	string guid;
	if (params.getStringNode(M_SENDER_PATH, &uiID) && params.getStringNode(M_GUID_PATH, &guid)) 	
		uiDeviceManager.uiDeviceBool(uiID, success, guid);
}

void RoomManager::updateRoom(ICommandCallback *parent, XMLParse params) {
	(static_cast<RoomManager*>(parent))->updateRoom(params);
}
void RoomManager::updateRoom(XMLParse params) {
	bool success = false;
	
	string id;
	if (params.getStringNode(M_ROOM_ID_PATH, &id)) {
		
		int idx = getRoomIndex(id);
		if (idx > -1) {
			
			string name;
			if (params.getStringNode(M_ROOM_NAME_PATH, &name)) {
				if (name.size() > 0) {
					
					// update room in database
					XMLBuild body("UpdateRoom");
					body.addAttribute("UpdateRoom", "xmlns", "http://tempuri.org/");
					body.addStringNode("UpdateRoom/room/b:RoomID", id);
					body.addStringNode("UpdateRoom/room/b:RoomName", name);
					body.addAttribute("UpdateRoom/room", "xmlns:b", "http://schemas.datacontract.org/2004/07/SmartSocketsWebService");
					body.addAttribute("UpdateRoom/room", "xmlns:i", "http://www.w3.org/2001/XMLSchema-instance");
					
					HTTPRequest req;
					string response;
					req.SOAPRequest(body.getXML(), "UpdateRoom", response);
					
					XMLParse reply(response);
					
					string requestOutcome;
					if (reply.getStringNode("//UpdateRoomResult", &requestOutcome)) {
						if (requestOutcome.compare("true") == 0) {
							allRooms[idx].setName(name);
							success = true;
							// send new room info to UI or upon recieveing the bool it can request it?
						}
					}
				}
			}
			
		}
	}
	
	// send success to UI device 
	string uiID;
	string guid;
	if (params.getStringNode(M_SENDER_PATH, &uiID) && params.getStringNode(M_GUID_PATH, &guid)) 	
		uiDeviceManager.uiDeviceBool(uiID, success, guid);
}

/**** Private Functions ***/

int RoomManager::getRoomIndex(string id) {
	int idx = -1;
	for (int i = 0; i < allRooms.size(); i++) {
		string roomID = allRooms[i].getID();
		if (id == roomID && id.size() == roomID.size()) {
			idx = i;
		}
	}
	
	return idx;
}

RoomManager roomManager;