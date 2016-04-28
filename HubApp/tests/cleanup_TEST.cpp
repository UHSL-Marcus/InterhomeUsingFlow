

#include "cleanup_TEST.h"

void doCleanup() {
	
	cout << "\n\nCleaning...";
	
	// remove all UI Devices
	vector<UIDevice> uiDevices = uiDeviceManager.getUIDevices();
	if (uiDevices.size() > 0) {
		cout << "\nClearing UI Devices...";

		for (int i = 0; i < uiDevices.size(); i++) {
			uiDeviceManager.removeUIDevice("<packet><data><ui_device_id>" + uiDevices[i].getID() + "</ui_device_id></data></packet>");
		}
		
		uiDevices = uiDeviceManager.getUIDevices();
		if (uiDevices.size() == 0)
		{
			cout << "UI Devices cleared";
		}
	}
	
	// remove all Devices
	vector<Device> devices = deviceManager.getDevices();
	vector<Device> pDevices = deviceManager.getPendingDevices();
	if (pDevices.size() > 0) {
		cout << "\nMoving Pending Devices...";

		for (int i = 0; i < pDevices.size(); i++) {
			deviceManager.addPendingDevice("<packet><data><mac_addr>" + pDevices[i].getMAC() + "</mac_addr><room_id>room1</room_id><device_name>" + pDevices[i].getMAC() +"</device_name></data></packet>");
		}
		
		pDevices = deviceManager.getPendingDevices();
		if (pDevices.size() == 0)
		{
			cout << "Pending Devices Moved";
		}
	}
	
	if (devices.size() > 0) {
		cout << "\nClearing Devices...";

		for (int i = 0; i < devices.size(); i++) {
			deviceManager.removeDevice("<packet><data><device_id>" + devices[i].getID() + "</device_id></data></packet>");
		}
		
		devices = deviceManager.getDevices();
		if (devices.size() == 0)
		{
			cout << "Devices cleared";
		}
	}
	
	// remove all Rooms
	vector<Room> rooms = roomManager.getRooms();
	if (rooms.size() > 0) {
		cout << "\nClearing Rooms...";

		for (int i = 0; i < rooms.size(); i++) {
			roomManager.removeRoom("<packet><data><room_id>" + rooms[i].getID() + "</room_id></data></packet>");
		}
		
		rooms = roomManager.getRooms();
		if (rooms.size() == 0)
		{
			cout << "Rooms cleared";
		}
	}
	
	// remove all Rooms device map pairs
	vector<string> roomPairs =  roomDeviceMapManager.getRooms();
	if (roomPairs.size() > 0) {
		cout << "\nClearing Room/device pairs...";

		for (int i = 0; i < roomPairs.size(); i++) {
			roomDeviceMapManager.removeRoom(roomPairs[i]);
		}
		
		roomPairs =  roomDeviceMapManager.getRooms();
		if (roomPairs.size() == 0)
		{
			cout << "Room/device pairs cleared";
		}
	}
	
	cout << "\nClean complete";
	
}

