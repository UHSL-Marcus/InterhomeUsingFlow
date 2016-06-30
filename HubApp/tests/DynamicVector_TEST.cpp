/********************************************************************
// **************************** main.cpp ****************************
/************************************ Author: Marcus Lee ***********/

#include "DynamicVector_TEST.h"


namespace DynamicVector_TEST {
	
}

using namespace DynamicVector_TEST;


void doDynamicVector_test() {
	
	cout << "\n******GETTING AN INT VECTOR**********\n";
	DynamicVector dynVect;
	
	vector<int> &intVect = dynVect.getVector<int>();
	
	cout << "\n******ADDING ENTRIES**********\n";
	
	intVect.push_back(1);
	intVect.push_back(109);
	intVect.push_back(6);
	intVect.push_back(9964);
	
	cout << "\n******ENTRY COUNT: " << intVect.size() << "**********\n";
	
	cout << "\n******GETTING A BOOL VECTOR**********\n";
	
	vector<bool> &boolVect = dynVect.getVector<bool>();
	
	cout << "\n******ADDING ENTRIES**********\n";
	
	boolVect.push_back(true);
	boolVect.push_back(false);
	boolVect.push_back(true);
	boolVect.push_back(true);
	
	cout << "\n******ENTRY COUNT: " << boolVect.size() << "**********\n";
	
	cout << "\n******RETREIVING BOTH VECTORS**********\n";
	
	vector<int>& intVect2 = dynVect.getVector<int>();
	vector<bool>& boolVect2 = dynVect.getVector<bool>();
	cout << "\n******INT ENTRY COUNT: " << intVect2.size() << "**********\n";
	cout << "\n******BOOL ENTRY COUNT: " << boolVect2.size() << "**********\n";
	
	
	
}