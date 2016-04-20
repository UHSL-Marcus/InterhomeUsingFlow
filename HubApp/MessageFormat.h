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
#define ROOM_NAME "name"
#define ROOM_NAME_PATH DATA_PATH"/"ROOM_NAME

#define ROOM_ID "name"
#define ROOM_ID_PATH DATA_PATH"/"ROOM_ID

// Device Manager
#define TEMP_ID "temp_id"
#define TEMP_ID_PATH DATA"/"TEMP_ID




#endif /* MESSAGE_FORMAT_H */