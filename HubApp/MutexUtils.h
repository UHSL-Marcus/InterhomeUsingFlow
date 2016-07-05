/********************************************************************
// *************************** MutexUtils.h *************************         
/************************************ Author: Marcus Lee ***********/

#ifndef MUTEX_UTILS_H
#define MUTEX_UTILS_H

#include <mutex>

class MutexUtils
{
	public:
		template< class Lockable>
		static void lock(Lockable& lock);
		template< class Lockable, class... Lockables>
		static void lock(Lockable& lock, Lockables&... locks);
};

template< class Lockable>
void MutexUtils::lock(Lockable& lock) {
	lock.lock();
}

template< class Lockable, class... Lockables>
void MutexUtils::lock(Lockable& lock, Lockables&... locks) {
	std::lock(lock, locks...);
}


#endif /* MUTEX_UTILS_H */