/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "RoomManager_TEST.h"


namespace ThreadManager_TEST {
	void testFunc(int i, string name) {
		string s = "\n" + name + " " + std::to_string(i) + " started";
		cout << s;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
		s = "\n" + name + " " + std::to_string(i) + " Ended";
		cout << s;
	}
}

using namespace ThreadManager_TEST;


void doThreadManager_test() {
	
	cout << "\n******STARTING THREADS**********\n";
	for (int i = 0; i < 15; i++) {
		string s = "\nThread " + std::to_string(i);
		cout << s;
		threadManager.startNewThread(testFunc, i, "Thread:");
		
		s = "\nRunning threads: " + std::to_string(threadManager.getRunningThreadCount());
		cout << s
	}
	
	cout << "\n******JOINING THREADS**********\n";
	threadManager.joinAllThreads();
	
	s = "\nAll threads joined\nRunning threads: " + std::to_string(threadManager.getRunningThreadCount());
	cout << s
	
}