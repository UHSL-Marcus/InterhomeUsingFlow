

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::vector;
using std::string;


class item {
	public:
		item() {cout << "\ncon empty";};
		item(string _word, int _num) : word(_word), num(_num), ver(0) {
			cout << "\ncon " << word << ", ver: " << ver;
		};
		item (const item &obj) : word(obj.word), num(obj.num), ver(obj.ver+1) {
			cout << "\ncopy " << word << ", ver: " << ver;
		}
		~item() {
			cout << "\ndes " << word << ", ver: " << ver;
		};
		item operator=(const item &obj) {
			word = obj.word; num = obj.num; ver = obj.ver+1;
			cout << "\n= Word: " << word << ", ver: " << ver;
			return *this;
		}
		void print() {
			cout << "\nPrint " << word << ", ver: " << ver << "\nWord: " << word << ", num: " << num;
		};
		void changeNum(int n) {
			num = n;
			cout << "\nchange " << word << ", ver: " << ver << ", num: " << num;
		}
	private:
		int num;
		string word;
		int ver;
};

class container {
	public:
		void addItem (string word, int num) {
			cout << "\n\ncreate";
			item temp(word, num);
			cout << "\n\npush";
			items.push_back(temp);
		}
		
		void getItem(int idx, item* out) {
			if (idx < items.size()) {
				cout << "\n\nextract";
				*out = items[idx];
			}
		}
		
		void printAll() {
			cout << "\n\nprint all in vector"; 
			for (int i = 0; i < items.size(); i++) {
				items[i].print();
			}
		}
	
	private:
		vector<item> items;
};

int main(void) {
	
	container con;
	con.addItem("word1", 1);
	con.addItem("word2", 2);
	
	
	item it;
	con.getItem(0, &it);
	it.changeNum(5);
	it.print();
	
	con.printAll();
	
	
	return 0;
}