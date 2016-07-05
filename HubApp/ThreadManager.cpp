/********************************************************************
// ************************* ThreadManager.cpp **********************       
/************************************ Author: Marcus Lee ***********/

#include "ThreadManager.h"

#include <iostream>
#include <string>

/**** Public Functions ***/

ThreadManager::ThreadManager() {
	
}

ThreadManager::~ThreadManager() {
	
}

void ThreadManager::removeCompletedThreads() {
	vector<future<void>>& threads = _threads.getVector<future<void>>();
	
	for (int i = 0; i < threads.size(); i++) {
        if (threads[i].wait_for(std::chrono::milliseconds(0)) == future_status::ready) 
			threads.erase(threads.begin() + i);
		
    }
}

void ThreadManager::joinAllThreads() {
	vector<future<void>>& threads = _threads.getVector<future<void>>();
	
	for (int i = 0; i < threads.size(); i++) {
		threads[i].wait();
		threads.erase(threads.begin() + i);
	}
	
	if (threads.size() > 0)
		joinAllThreads();
}

int ThreadManager::getRunningThreadCount() {
	removeCompletedThreads();
	return _threads.getVector<future<void>>().size();
}

ThreadManager threadManager;

/**** Private Functions ***/