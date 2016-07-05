/********************************************************************
// ************************* MutexCheckable.h ***********************         
/************************************ Author: Marcus Lee ***********/

#ifndef MUTEX_CHECKABLE_H
#define MUTEX_CHECKABLE_H

#include <mutex>
#include <thread>

class MutexCheckable : public std::mutex
{
	public:
		void lock();
		void unlock();
		bool is_locked() const;

	private:
		std::thread::id owner = std::thread::id();
};

#endif /* MUTEX_CHECKABLE_H */