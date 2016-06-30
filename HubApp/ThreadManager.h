/********************************************************************
// ************************* ThreadManager.h ************************         
/************************************ Author: Marcus Lee ***********/

#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <future>
#include <vector>
#include <chrono>

#include "DynamicVector.h"

using std::thread;
using std::vector;
using std::future;
using std::future_status;
using std::async;


class ThreadManager {
	public:
		ThreadManager();
		~ThreadManager();
		template< class Function, class... Args > 
		void startNewThread(Function f, Args ...args);
		void joinAllThreads();
		void removeCompletedThreads();
		int getRunningThreadCount();
	private:
		DynamicVector _threads;
	
};

extern ThreadManager threadManager;

template<class Function, class ...Args> 
void ThreadManager::startNewThread(Function f, Args ...args) {
	
	removeCompletedThreads();
	
	_threads.getVector<future<void>>().push_back(async(std::launch::async, f, args...));
	
}


#endif /* THREAD_MANAGER_H */