// 8.2 Design a call center system to handle calls, the order will be respondent->manager->director, find the first employee to handle a call.
#include <iostream>
#include <vector>
using namespace std;

class People {
public:
	People() {};
	virtual void handle() = 0;
	virtual ~People() {};
};

class Respondent: public People {
public:
	Respondent() {};
	void handle() {
		cout << "Respondent is handling the call." << endl;
	};
	~Respondent() {};
};

class Manager: public People {
public:
	Manager() {};
	void handle() {
		cout << "Manager is handling the call." << endl;
	};
	~Manager() {};
};

class Director: public People {
public:
	Director() {};
	void handle() {
		cout << "Director is handling the call." << endl;
	};
	~Director() {};
};

class CallCenter {
public:
	CallCenter(int num_respondent = 0, int num_manager = 0, int num_director = 0) {
		respondents.resize(num_respondent);
		managers.resize(num_manager);
		directors.resize(num_director);
		respondents_available.resize(num_respondent);
		managers_available.resize(num_manager);
		directors_available.resize(num_director);
		fill(respondents_available.begin(), respondents_available.end(), true);
		fill(managers_available.begin(), managers_available.end(), true);
		fill(directors_available.begin(), directors_available.end(), true);
	}
	
	void handle() {
		size_t i;
		
		for (i = 0; i < respondents.size(); ++i) {
			if (respondents_available[i]) {
				break;
			}
		}
		if (i < respondents.size()) {
			respondents_available[i] = false;
			respondents[i].handle();
			respondents_available[i] = true;
			return;
		}

		for (i = 0; i < managers.size(); ++i) {
			if (managers_available[i]) {
				break;
			}
		}
		if (i < managers.size()) {
			managers_available[i] = false;
			managers[i].handle();
			managers_available[i] = true;
			return;
		}
		
		for (i = 0; i < directors.size(); ++i) {
			if (directors_available[i]) {
				break;
			}
		}
		if (i < directors.size()) {
			directors_available[i] = false;
			directors[i].handle();
			directors_available[i] = true;
			return;
		}
	}
private:
	vector<Respondent> respondents;
	vector<Manager> managers;
	vector<Director> directors;
	vector<bool> respondents_available;
	vector<bool> managers_available;
	vector<bool> directors_available;
};

int main()
{
	CallCenter *p_call_center = nullptr;
	int r, m, d;
	
	while (cin >> r >> m >> d) {
		p_call_center = new CallCenter(r, m, d);
		p_call_center->handle();
		delete p_call_center;
		p_call_center = nullptr;
	}
	
	return 0;
}