/********************************************************************
// ************************ CommandHandler.h ************************
/*******************************************************************/
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <cstring>
#include <vector>

#define MAX_CALLBACKS 50
#define COMMAND_MAX_LENGTH 20

using std::vector;

class ICommandCallback {};

typedef void (*CommandCallbackFunction)(ICommandCallback *parent);

typedef struct
{
	char command[COMMAND_MAX_LENGTH];
	CommandCallbackFunction callback;
	ICommandCallback *parent;
} CommandBinding;

class CommandHandler
{
	public:
		CommandHandler();
		bool addCallback(char * cmd, CommandCallbackFunction callback, ICommandCallback *parent);
		bool updateCallack(char * cmd, CommandCallbackFunction callback, ICommandCallback *parent);
		bool handleCmd(char * cmd);
	private:
		std::vector<CommandBinding> callbacks;
		std::vector<CommandBinding> findBindings(char * cmd);
		std::vector<CommandBinding> findBindings(char * cmd, ICommandCallback *parent);
};
extern CommandHandler commandHandler;



#endif /* COMMAND_HANDLER_H */ 