/********************************************************************
// *********************** RoomDeviceMapManager.cpp ************************   
/************************************ Author: Marcus Lee ***********/

#include "RoomDeviceMapManager.h"

#include <iostream>

/**** Public Functions ****/

RoomDeviceMapManager::RoomDeviceMapManager() {
	
}

bool RoomDeviceMapManager::addRoom(string id) {
	map<string,vector<string> >::iterator itr;
	
	unique_lock<MutexCheckable> guard;
	if (!getRoomIterator(id, &itr, &guard)) {
		vector<string> toInsert;
		roomDeviceMap.insert(std::pair<string,vector<string> >(id,toInsert));
		return true;
	}
	return false;
}

bool RoomDeviceMapManager::removeRoom(string id) {
	
	map<string,vector<string> >::iterator itr;
	
	unique_lock<MutexCheckable> guard;
	if (getRoomIterator(id, &itr, &guard)) {
		roomDeviceMap.erase(itr);
		return true;
	}
	return false;
}

bool RoomDeviceMapManager::addDevice(string room_id, string device_id) {
	
	std::cout << "***Add device";
	
	map<string,vector<string> >::iterator itr;

	unique_lock<MutexCheckable> guard;
	if (getRoomIterator(room_id, &itr, &guard)) {
		vector<string>& devices = itr->second;
		bool exist = false;
		for (int i = 0; i < devices.size(); i++) {
			if (devices[i] == device_id) {
				exist = true;
				break;
			}
		}
		if (!exist) {
			devices.push_back(device_id);
			return true;
		}
	}
	
	return false;
}

bool RoomDeviceMapManager::removeDevice(string device_id) {
	
	int idx;
	map<string,vector<string> >::iterator itr;
	
	unique_lock<MutexCheckable> guard;
	if (getDeviceIndexAndRoomIterator(device_id, &itr, &idx, &guard)) {
		vector<string>& devices = itr->second;
		devices.erase(devices.begin()+idx);
		return true;
	}
	
	return false;
}

bool RoomDeviceMapManager::getDeviceRoom(string id, string* out) {
	
	map<string,vector<string> >::iterator itr;
	
	unique_lock<MutexCheckable> guard;
	if (getDeviceIndexAndRoomIterator(id, &itr, NULL, &guard)) {
		*out = itr->first;
		return true;
	}
	
	return false;
}

bool RoomDeviceMapManager::getRoomDevices(string id, vector<string>* out) {

	map<string,vector<string> >::iterator itr;
	
	unique_lock<MutexCheckable> guard;
	if (getRoomIterator(id, &itr, &guard)) {
		*out = itr->second;
		return true;
	}
	return false;
}

vector<string> RoomDeviceMapManager::getRooms() {
	
	vector<string> rooms;
	
	unique_lock<MutexCheckable> guard(roomDeviceMapMutex);
	for (map<string,vector<string> >::iterator itr = roomDeviceMap.begin(); itr != roomDeviceMap.end(); ++itr) {
		rooms.push_back(itr->first);
	}
	
	return rooms;
	
}

/**** Private Functions ****/

bool RoomDeviceMapManager::getRoomIterator(string id, map<string,vector<string> >::iterator* out, unique_lock<MutexCheckable> *outLock) {

	if (!roomDeviceMapMutex.is_locked()) 
		*outLock = unique_lock<MutexCheckable>(roomDeviceMapMutex);
	
	map<string,vector<string> >::iterator itr = roomDeviceMap.find(id);
	if (itr != roomDeviceMap.end()) {
		*out = itr;
		return true;
	}
	
	
	return false;
}

bool RoomDeviceMapManager::getDeviceIndexAndRoomIterator(string id, map<string,vector<string> >::iterator* itrOut, int *idxOut, unique_lock<MutexCheckable> *outLock) {

	if (!roomDeviceMapMutex.is_locked()) 
		*outLock = unique_lock<MutexCheckable>(roomDeviceMapMutex);
	
	for (map<string,vector<string> >::iterator itr = roomDeviceMap.begin(); itr != roomDeviceMap.end(); ++itr) {
		vector<string> devices = itr->second;
		for (int i = 0; i < devices.size(); i++) {
			if (devices[i] == id) {
				
				if (itrOut != NULL)
					*itrOut = itr;
			
				if (idxOut != NULL)
					*idxOut = i;
				

				return true;
			}
		}
	}
	return false;
}

RoomDeviceMapManager roomDeviceMapManager;

