#ifndef MESSAGE_FORMAT_H
#define MESSAGE_FORMAT_H


// General
#define ROOT "packet"
#define GUID "guid"
#define SENDER "from"
#define RECIPTIENT "to"
#define TIMESTAMP "timestamp"
#define DATA "data"

#define GUID_PATH ROOT"/"GUID
#define SENDER_PATH ROOT"/"SENDER
#define RECIPTIENT_PATH ROOT"/"RECIPTIENT
#define TIMESTAMP_PATH ROOT"/"TIMESTAMP
#define DATA_PATH ROOT"/"DATA

// Room Manager
#define ROOM_NAME "room_name"
#define ROOM_NAME_PATH DATA_PATH"/"ROOM_NAME

#define ROOM_ID "room_id"
#define ROOM_ID_PATH DATA_PATH"/"ROOM_ID

// Device Manager
#define TEMP_ID "temp_id"
#define TEMP_ID_PATH DATA_PATH"/"TEMP_ID

#define DEVICE_NAME "device_name"
#define DEVICE_NAME_PATH DATA_PATH"/"DEVICE_NAME

#define DEVICE_TYPE "device_type"
#define DEVICE_TYPE_PATH DATA_PATH"/"DEVICE_TYPE

#define DEVICE_ID "device_id"
#define DEVICE_ID_PATH DATA_PATH"/"DEVICE_ID

// UI Device Manager
#define UI_DEVICE_ID "ui_device_id"
#define UI_DEVICE_ID_PATH DATA_PATH"/"UI_DEVICE_ID

#define UI_DEVICE_NAME "ui_device_name"
#define UI_DEVICE_NAME_PATH DATA_PATH"/"UI_DEVICE_NAME



#endif /* MESSAGE_FORMAT_H */