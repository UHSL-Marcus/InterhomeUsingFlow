
#include <iostream>
#include <vector>

using std::cout;
using std::vector;


class item {
	public:
		item() {
			cout << "\n con";
			info = 2;
		};
		~item() {
			cout << "\n des";
		};
		int getInfo() {
			return info;
		};
	private:
		int info;
};


class conatiner {
	public:
		void doTest() {
			item* _item = new item;
			cout << "\nitem* is: " << _item;
			cout << "\nitem info is: " << _item->getInfo();
			items.push_back(*_item);
			listItems();
			delete _item;
			cout << "\nitem* is: " << _item;
			cout << "\nitem info is: " << _item->getInfo();
			listItems();
		};
		
		void listItems() {
			cout << "\nlisting items";
			for (int i = 0; i < items.size(); i++) {
				cout << "\nitem info is: " << items[i].getInfo();
			}
		};
		
	private:
		vector<item> items;
};


int main(void) {
	
	conatiner con;
	
	con.doTest();
	cout << "\nfrom main";
	con.listItems();
	
	return 0;
}