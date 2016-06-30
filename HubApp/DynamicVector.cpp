/********************************************************************
// ************************ DynamicVector.cpp ***********************       
/************************************ Author: Marcus Lee ***********/

#include "DynamicVector.h"

/**** Public Functions ***/


/**** Private Functions ***/


int DynamicVector::type_index_alloc() {
	static atomic<int> current(0);
    return ++current;
}