/********************************************************************
// ************************ CommandHandler.h ************************
/*******************************************************************/




#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#define MAX_CALLBACKS 50;

typedef void (*CommandCallbackFunction)();

typedef struct
{
	char command[COMMAND_MAX_LENGTH];
	CommandCallbackFunction callback;
} CommandBinding;

class CommandHandler
{
	public:
		CommandHandler();
		bool addCallback(char * cmd, CommandCallbackFunction callback);
		bool updateCallack(char * cmd, CommandCallbackFunction callback);
		bool handleCmd(char * cmd);
	private:
		CommandBinding callbacks[MAX_CALLBACKS];
		int bindingCount;
}
extern CommandHandler commandHandler;

#endif /* COMMAND_HANDLER_H */ 