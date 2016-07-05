/********************************************************************
// ************************ MutexCheckable.cpp **********************        
/************************************ Author: Marcus Lee ***********/

#include "MutexCheckable.h"

#include <iostream>

/**** Public Functions ***/

void MutexCheckable::lock()
{
	//std::cout << "\ntry lock " << std::this_thread::get_id();
	std::mutex::lock();
	//std::cout << "\nlocked " << std::this_thread::get_id();
	owner = std::this_thread::get_id(); 
}

void MutexCheckable::unlock()
{
	//std::cout << "\nunlock " << std::this_thread::get_id();
	owner = std::thread::id();
	std::mutex::unlock();
	//std::cout << "\nunlocked " << std::this_thread::get_id();
}

bool MutexCheckable::is_locked() const
{
	//std::cout << "\n" << owner << " = " << std::this_thread::get_id();
	return owner == std::this_thread::get_id();
}

/**** Private Functions ***/