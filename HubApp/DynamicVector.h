/********************************************************************
// ************************* DynamicVector.h ************************         
/************************************ Author: Marcus Lee ***********/


/********************************************************************
// ************************* DynamicVector.h ************************       
/************************************ Author: Marcus Lee ***********/

#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <atomic>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <typeinfo>
#include <memory>

using std::map;
using std::shared_ptr;
using std::vector;
using std::pair;
using std::make_shared;
using std::atomic;



class DynamicVector {
	public:
		template <typename T>
		vector<T>& getVector();
	
	private:
		template <typename T>
		int type_map();
		int type_index_alloc();
		struct BaseContainer {};
		template <typename T>
		struct TypeContainer : BaseContainer {
			vector<T> store;
		};
		
		map<int, shared_ptr<BaseContainer>> vals_;
};


/**** Public Functions ***/

template <typename T>
vector<T>& DynamicVector::getVector() {
	pair<std::map<int, shared_ptr<BaseContainer>>::iterator,bool> ret;
			
	shared_ptr<BaseContainer> bc = make_shared<TypeContainer<T>>();

	ret = vals_.insert(pair<int, shared_ptr<BaseContainer>>(type_map<T>(), bc));
	
	return static_cast<TypeContainer<T>&>(*(ret.first->second)).store;
}


/**** Private Functions ***/

template <typename T>
int DynamicVector::type_map() {
	static int rc = type_index_alloc();
	return rc;
}

#endif /* DYNAMIC_VECTOR_H */