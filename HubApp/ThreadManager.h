/********************************************************************
// ************************* ThreadManager.h ************************         
/************************************ Author: Marcus Lee ***********/

#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <thread>
#include <future>
#include <vector>
#include <chrono>

using std::thread;
using std::vector;
using std::future;
using std::packaged_task;

template<typename T>
struct ThreadEntry
{
	thread _thread;
	future<T> _future;
}; 

class ThreadManager {
	public:
		ThreadManager();
		~ThreadManager();
		template< class Function, class... Args > 
		void startNewThread(Function&& f, Args&&... args);
		void joinAllThreads();
		void removeCompletedThreads();
		int getRunningThreadCount();
	private:
		vector<ThreadEntry<T> > threads;
	
};

extern ThreadManager threadManager;


#endif /* THREAD_MANAGER_H */