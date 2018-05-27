// 8.4 Design a class to simulate the parking lot.
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class ParkingLot {
public:
	ParkingLot(int _capacity = 0):capacity(_capacity) {
		slots.resize(capacity);
		fees.resize(capacity);
		fill(slots.begin(), slots.end(), false);
		fill(fees.begin(), fees.end(), 0);
	};
	
	void start() {
		work = new thread(workThread, this);
	};
	
	void parkIn() {
		int i;
		
		for (i = 0; i < (int)slots.size(); ++i) {
			if (!slots[i]) {
				cout << "Car is parked at slot " << i << "." << endl;
				slots[i] = true;
				fees[i] = 1;
				return;
			}
		}
		
		cout << "Sorry, no more slot is available." << endl;
	};
	
	void getOut(int id) {
		if (id < 0 || id > (int)slots.size() - 1) {
			cout << "Invalid slot number." << endl;
			return;
		} else if (slots[id] == false) {
			cout << "The slot is empty." << endl;
			return;
		}
		
		cout << "Car in slot " << id << " is delivered. Total fee is " << fees[id] << " bucks." << endl;
		slots[id] = false;
		fees[id] = 0;
	};
	
	friend void workThread(ParkingLot *);
	
	~ParkingLot() {
		slots.clear();
		fees.clear();
		work->detach();
		delete work;
	};
private:
	thread *work;
	int capacity;
	vector<bool> slots;
	vector<int> fees;
};

void workThread(ParkingLot *p)
{
	while (true) {
		// sleep for one second.
		_sleep(1000);
		for (int i = 0; i < p->capacity; ++i) {
			if (p->slots[i]) {
				++p->fees[i];
			}
		}
	}
}

int main()
{
	ParkingLot *p;
	string cmd;
	int id;
	
	p = new ParkingLot(5);
	p->start();
	while (cin >> cmd) {
		if (cmd == "park") {
			p->parkIn();
		} else if (cmd == "get") {
			cin >> id;
			p->getOut(id);
		} else if (cmd == "end") {
			break;
		}
	}
	delete p;
	
	return 0;
}