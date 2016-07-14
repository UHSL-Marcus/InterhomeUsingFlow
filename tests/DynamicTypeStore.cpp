#include <atomic>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <typeinfo>
#include <memory>

int type_index_alloc() { 
    static std::atomic<int> current(0);
    return ++current;
}

template <typename T>
int type_map() {
    static int rc = type_index_alloc();
	return rc;
}

struct BaseContainer {};

template <typename T>
struct TypeContainer : BaseContainer {
	std::vector<T> store;
};

std::map<int, std::shared_ptr<BaseContainer>> vals_;



class Container {
	public:
		template <typename T>
		std::vector<T>& items() {
			std::pair<std::map<int, std::shared_ptr<BaseContainer>>::iterator,bool> ret;
			
			std::shared_ptr<BaseContainer> bc = std::make_shared<TypeContainer<T>>();

			ret = vals_.insert(std::pair<int, std::shared_ptr<BaseContainer>>(type_map<T>(), bc));
			
			//std::cout << "\n" << typeid(ret.first->second).name();
			
			return static_cast<TypeContainer<T>&>(*(ret.first->second)).store;
			
		}  
};


int main(void) {
	std::cout << "\nStarted";
	std::cout << "\nGetting a vector of int";
	
	Container cont;
	
	std::vector<int> &int_vector = cont.items<int>();
	
	std::cout << "\nGetting a vector of bool";
	
	std::vector<bool> &bool_vector = cont.items<bool>();
	
	std::cout << "\nAdding some ints";
	
	int_vector.push_back(1);
	int_vector.push_back(3);
	int_vector.push_back(5);
	
	
	std::cout << "\nAdding some bools";
	
	bool_vector.push_back(true);
	bool_vector.push_back(false);
	bool_vector.push_back(true);
	
	std::cout << "\nNumber of ints: " << int_vector.size();
	std::cout << "\nNumber of bools: " << bool_vector.size();
	
	std::cout << "\nRetrieving both vectors again";
	std::vector<int> int_vector2 = cont.items<int>();
	std::vector<bool> bool_vector2 = cont.items<bool>();
	
	std::cout << "\nNumber of ints: " << int_vector2.size();
	std::cout << "\nNumber of bools: " << bool_vector2.size();
	
	
	std:: cout << "\n\n";
	return 0;
}