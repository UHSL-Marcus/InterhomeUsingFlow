#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <string>

using std::thread;
using std::cout;
using std::vector;
using std::string;

int count = 0;
std::mutex counter_mutex;

vector<thread> threads;

void func (int i)
{
	cout << "\nThread " << i << "\n";
	std::lock_guard<std::mutex> guard(counter_mutex);
	int start_count = count;
	for (int c = 0; c < 100; c++ ) {
		
		count++;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
	string s = "\nthread " + std::to_string(i) + ": " + std::to_string(start_count) + " -> " + std::to_string(count);
	cout << s;
}

int main(void) 
{
	cout << "start";
	for (int i = 1; i<6; i++) {
		threads.push_back(thread(func, i));
	}
	
	for(auto& thread : threads){
        thread.join();
    }
	
	cout << "\nAll created: " << count << "\n";
	
	
	
	
	return 0;
}	