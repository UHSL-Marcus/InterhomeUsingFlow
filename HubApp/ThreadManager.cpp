/********************************************************************
// ************************* ThreadManager.cpp **********************       
/************************************ Author: Marcus Lee ***********/

#include "ThreadManager.h"

ThreadManager::ThreadManager() {
	
}
ThreadManager::~ThreadManager() {
	
}

void ThreadManager::startNewThread(Function&& f, Args&&... args) {
	
	ThreadEntry<void> te;
	packaged_task<void(args...)> task(f);
	
	te._future = task.get_future();
	te._thread = thread(std::move(task), args...);
	
	removeCompletedThreads();
	
	threads.push_back(te);
}

void ThreadManager::removeCompletedThreads() {
	
	for (int i = 0; i < threads.size(); i++) {
		ThreadEntry te = threads[i];
		
        if (te._future.wait_for(std::chrono::milliseconds(0)) == future_status::ready) {
			te._thread.join();
			threads.erase(threads.begin() + i);
		}
    }
}

void ThreadManager::joinAllThreads() {
	for (int i = 0; i < threads.size(); i++) {
		ThreadEntry te = threads[i];
		te._thread.join();
		threads.erase(threads.begin() + i);
	}
}

int ThreadManager::getRunningThreadCount() {
	removeCompletedThreads();
	return threads.size();
}

ThreadManager threadManager;