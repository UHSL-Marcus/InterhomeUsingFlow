/********************************************************************
// **************************** State.h *****************************          
/*******************************************************************/

#ifndef STATE_H
#define STATE_H

// General States
#define HEARTBEAT "heartbeat_state"
#define CONNECTED "connected_state"

#define GENERAL_STATE_LIST HEARTBEAT","CONNECTED

// CONNECTED state options
#define CONNECTED_ON "connected_state_on"
#define CONNECTED_OFF "connected_state_off"
#define CONNECTED_INTERMITTENT "connected_state_intermittent"

// Socket States
#define VOLTAGE "voltage_state"
#define CURRENT "current_state"
#define POWER "power_state"

#define SOCKET_STATE_LIST VOLTAGE","CURRENT","POWER


#endif /* STATE_H */