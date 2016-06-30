/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "ThreadManager_TEST.h"


namespace ThreadManager_TEST {
	void testFunc(int i, string name) {
		string s = "\n\n*THREAD " + std::to_string(i) + " STARTED (" + name + ")*";
		cout << s;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
		s = "\n\n*THREAD " + std::to_string(i) + " ENDED (" + name + ")*";
		cout << s;
	}
}

using namespace ThreadManager_TEST;


void doThreadManager_test() {
	
	cout << "\n\n******STARTING THREADS**********\n";
	cout << "Running threads: " + std::to_string(threadManager.getRunningThreadCount());
	for (int i = 0; i < 15; i++) {
		string s = "\n\n*STARTING THREAD " + std::to_string(i) + "*";
		
		threadManager.startNewThread(testFunc, i, "Thread" + std::to_string(i));
		
		s += "\nRunning threads: " + std::to_string(threadManager.getRunningThreadCount());
		cout << s;
	}
	
	cout << "\n\n******JOINING THREADS**********\n";
	threadManager.joinAllThreads();
	
	string s = "\n\n******THREADS JOINED**********\nRunning threads: " + std::to_string(threadManager.getRunningThreadCount());
	cout << s;
	
}