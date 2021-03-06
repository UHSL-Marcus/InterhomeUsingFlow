#ifndef MESSAGE_FORMAT_H
#define MESSAGE_FORMAT_H


// General
#define M_ROOT "packet"
#define M_GUID "guid"
#define M_SENDER "from"
#define M_RECIPTIENT "to"
#define M_TYPE "type"
#define M_TIMESTAMP "timestamp"
#define M_DATA "data"

#define M_GUID_PATH M_ROOT "/" M_GUID
#define M_SENDER_PATH M_ROOT "/" M_SENDER
#define M_RECIPTIENT_PATH M_ROOT "/" M_RECIPTIENT
#define M_TYPE_PATH M_ROOT "/" M_TYPE
#define M_TIMESTAMP_PATH M_ROOT "/" M_TIMESTAMP
#define M_DATA_PATH M_ROOT "/" M_DATA

// Room Manager
#define M_ROOM_NAME "room_name"
#define M_ROOM_NAME_PATH M_DATA_PATH "/" M_ROOM_NAME

#define M_ROOM_ID "room_id"
#define M_ROOM_ID_PATH M_DATA_PATH "/" M_ROOM_ID

// Device Manager
#define M_DEVICE_MAC "mac_addr"
#define M_DEVICE_MAC_PATH M_DATA_PATH "/" M_DEVICE_MAC

#define M_DEVICE_NAME "device_name"
#define M_DEVICE_NAME_PATH M_DATA_PATH "/" M_DEVICE_NAME

#define M_DEVICE_TYPE "device_type"
#define M_DEVICE_TYPE_PATH M_DATA_PATH "/" M_DEVICE_TYPE

#define M_DEVICE_TYPE_ID "device_type_id"
#define M_DEVICE_TYPE_ID_PATH M_DATA_PATH "/" M_DEVICE_TYPE_ID

#define M_DEVICE_ID "device_id"
#define M_DEVICE_ID_PATH M_DATA_PATH "/" M_DEVICE_ID

#define M_DEVICE_CMD "device_cmd"
#define M_DEVICE_CMD_PATH M_DATA_PATH "/" M_DEVICE_CMD

#define M_DEVICE_CMD_DATA "device_cmd_data"
#define M_DEVICE_CMD_DATA_PATH M_DATA_PATH "/" M_DEVICE_CMD_DATA

#define M_DEVICE_STATE_PAIR "state_pair"
#define M_DEVICE_STATE_PAIR_PATH M_DATA_PATH "/" M_DEVICE_STATE_PAIR

#define M_DEVICE_STATE_NAME "state_name"
#define M_DEVICE_STATE_VALUE "state_value"


#define M_PRIMARY_COMMS "primary_communication"
#define M_PRIMARY_COMMS_PATH M_DATA_PATH "/" M_PRIMARY_COMMS

#define M_BACKUP_COMMS "backup_communication"
#define M_BACKUP_COMMS_PATH M_DATA_PATH "/" M_BACKUP_COMMS

// UI Device Manager
#define M_UI_DEVICE_ID "ui_device_id"
#define M_UI_DEVICE_ID_PATH M_DATA_PATH "/" M_UI_DEVICE_ID

#define M_UI_DEVICE_NAME "ui_device_name"
#define M_UI_DEVICE_NAME_PATH M_DATA_PATH "/" M_UI_DEVICE_NAME

#define M_UI_DEVICE_MESSAGE "ui_device_message"
#define M_UI_DEVICE_MESSAGE_PATH M_DATA_PATH "/" M_UI_DEVICE_MESSAGE

#define M_UI_DEVICE_BOOL "ui_device_bool"
#define M_UI_DEVICE_BOOL_PATH M_DATA_PATH "/" M_UI_DEVICE_BOOL



#endif /* MESSAGE_FORMAT_H */