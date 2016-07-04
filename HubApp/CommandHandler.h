/********************************************************************
// ************************ CommandHandler.h ************************
/************************************ Author: Marcus Lee ***********/
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>
#include <vector>
#include <thread>

#include "XMLUtil.h"
#include "ThreadManager.h"

#define MAX_CALLBACKS 50

using std::vector;
using std::string;
using std::thread;

/** Interface to be implimented by classes that use the CommandHandler
    */
class ICommandCallback {};

/** Definition of the callback functions to be implimented in the classes using the CommandHandler
    *
    * @param *parent 	Pointer to the object that set this callback 
	* @param params		XMLParse object holding the command infomation 	
    */
typedef void (*CommandCallbackFunction)(ICommandCallback *parent, XMLParse params);

typedef struct
{
	string command;
	CommandCallbackFunction callback;
	ICommandCallback *parent;
} CommandBinding;

/** Maps command strings with callback functions. When a command is recieved the correspoding callback functions will be called.
    *
    */
class CommandHandler
{
	public:
		CommandHandler();
		
		/** Adds a map of command and callback function, along with the object setting the map.
			*
			* @param cmd		The command string 
			* @param callback	The callback function
			* @param *parent	Pointer to the object setting this map 
			*/
		bool addCallback(string cmd, CommandCallbackFunction callback, ICommandCallback *parent);
		
		/** Updates a map of command and callback function.
			*
			* @param cmd		The command string 
			* @param callback	The callback function
			* @param *parent	Pointer to the object updating this map 
			*/
		bool updateCallack(string cmd, CommandCallbackFunction callback, ICommandCallback *parent);
		
		/** Calls the correspoding functions from the passed command.
			*
			* @param cmd		The command string 
			* @param params		XMLParse object holding the command infomation
			*/
		bool handleCmd(string cmd, XMLParse params);

	private:
		vector<CommandBinding> callbacks;
		vector<CommandBinding> findBindings(string cmd);
		vector<CommandBinding> findBindings(string cmd, ICommandCallback *parent);

};

/** The refrence of CommandHandler to be used.
    *
    */
extern CommandHandler commandHandler;



#endif /* COMMAND_HANDLER_H */ 