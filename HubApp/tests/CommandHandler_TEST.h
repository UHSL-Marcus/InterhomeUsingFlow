

#ifndef COMMAND_HANDLER_TEST_H
#define COMMAND_HANDLER_TEST_H

#include "../XMLUtil.h"
#include "../CommandHandler.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

void doCommandHandler_test();

class Temp : public ICommandCallback {
	public:
		Temp();
		static void callback(ICommandCallback *parent, XMLParse params);
		void add();
};

extern Temp temp;

#endif /* COMMAND_HANDLER_TEST_H */