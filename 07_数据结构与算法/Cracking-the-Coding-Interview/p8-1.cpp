// 8.1 Implement a class to simulate a deck of cards
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

struct Poker {
	int index;
	Poker(int _index = 0): index(_index) {};
	
	friend ostream& operator << (ostream &, const Poker &);
};

ostream& operator << (ostream &cout, const Poker &p)
{
	cout << '[';
	if (p.index < 0 || p.index > 53) {
		cout << "ERROR";
	} else if (p.index == 52) {
		cout << "BLACK JOKER";
	} else if (p.index == 53) {
		cout << "RED JOKER";
	} else {
		switch(p.index / 13) {
		case 0:
			cout << "SPADE ";
			break;
		case 1:
			cout << "HEART ";
			break;
		case 2:
			cout << "CLUB ";
			break;
		case 3:
			cout << "DIAMOND ";
			break;
		}
		switch(p.index % 13) {
		case 0:
			cout << 'A';
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			cout << char('1' + p.index % 13);
			break;
		case 9:
			cout << "10";
			break;
		case 10:
			cout << 'J';
			break;
		case 11:
			cout << 'Q';
			break;
		case 12:
			cout << 'K';
			break;
		}
	}
	cout << ']';
	
	return cout;
}

struct PokerListNode {
	Poker p;
	PokerListNode *next;
	PokerListNode(int _index): p(_index), next(nullptr) {};
};

class DeckOfPoker {
public:
	DeckOfPoker() {
		int i;
		
		head = tail = nullptr;
		for (i = 0; i < 54; ++i) {
			if (head == nullptr) {
				head = tail = new PokerListNode(i);
			} else {
				tail->next = new PokerListNode(i);
				tail = tail->next;
			}
			dict.insert(i);
		}
	}
	
	friend ostream& operator << (ostream &, const DeckOfPoker &);
	
	Poker peekCard() {
		if (head == nullptr) {
			return Poker(-1);
		} else {
			return head->p;
		}
	}
	
	Poker getCard() {
		if (head == nullptr) {
			return Poker(-1);
		} else {
			Poker p = head->p;
			PokerListNode *ptr = head;
			head = head->next;
			delete ptr;
			if (head == nullptr) {
				tail = nullptr;
			}
			dict.erase(p.index);
			
			return p;
		}
	}
	
	void insertCard(int index) {
		if (index < 0 || index > 53) {
			return;
		}
		if (dict.find(index) != dict.end()) {
			return;
		}
		
		PokerListNode *ptr = new PokerListNode(index);
		if (head == nullptr) {
			head = tail = ptr;
		} else {
			ptr->next = head;
			head = ptr;
		}
		dict.insert(index);
	}
	
	bool empty() {
		return head == nullptr;
	}
	
	void cutCards() {
		if (head == tail) {
			return;
		}
		
		PokerListNode *p1, *p2;
		p1 = p2 = head;
		while (p2->next != nullptr && p2->next->next != nullptr) {
			p1 = p1->next;
			p2 = p2->next->next;
		}
		PokerListNode *head2 = p1->next;
		p1->next = nullptr;
		
		PokerListNode *new_head, *new_tail;
		
		new_head = new_tail = nullptr;
		p1 = head;
		p2 = head2;
		while (p1 != nullptr && p2 != nullptr) {
			if (new_tail == nullptr) {
				new_head = new_tail = p1;
			} else {
				new_tail->next = p1;
				new_tail = new_tail->next;
			}
			p1 = p1->next;
			new_tail->next = nullptr;
			
			new_tail->next = p2;
			new_tail = new_tail->next;
			p2 = p2->next;
			new_tail->next = nullptr;
		}
		while (p1 != nullptr) {
			new_tail->next = p1;
			new_tail = new_tail->next;
			p1 = p1->next;
			new_tail->next = nullptr;
		}
		while (p2 != nullptr) {
			new_tail->next = p2;
			new_tail = new_tail->next;
			p2 = p2->next;
			new_tail->next = nullptr;
		}
		
		head = new_head;
		tail = new_tail;
	}
	
	void shuffleCards() {
		if (head == tail) {
			// no card or one card only
			return;
		}
		
		PokerListNode *p1, *p2;
		
		p1 = p2 = head;
		while (p2->next != nullptr && p2->next->next != nullptr) {
			p1 = p1->next;
			p2 = p2->next->next;
		}
		tail->next = head;
		head = p1->next;
		p1->next = nullptr;
		tail = p1;
	}
	
	~DeckOfPoker() {
		PokerListNode *ptr;
		
		while (head != nullptr) {
			ptr = head;
			head = head->next;
			delete ptr;
		}
		tail = head;
		dict.clear();
	}
private:
	PokerListNode *head;
	PokerListNode *tail;
	unordered_set<int> dict;
};

ostream& operator << (ostream& cout, const DeckOfPoker &deck)
{
	cout << '{' << endl;
	if (deck.head == nullptr) {
		cout << "EMPTY" << endl;
	} else {
		PokerListNode *ptr = deck.head;
		
		while (ptr != nullptr) {
			cout << ptr->p << endl;
			ptr = ptr->next;
		}
	}
	cout << '}' << endl;

	return cout;
}

int main()
{
	DeckOfPoker *deck = new DeckOfPoker();
	string s;
	int index;
	
	while (cin >> s) {
		if (s == "insert") {
			cin >> index;
			deck->insertCard(index);
		} else if (s == "peek") {
			cout << deck->peekCard() << endl;
		} else if (s == "get") {
			cout << deck->getCard() << endl;
		} else if (s == "shuffle") {
			deck->shuffleCards();
		} else if (s == "cut"){
			deck->cutCards();
		} else if (s == "print"){
			cout << *deck << endl;
		}
	}
	delete deck;
	
	return 0;
}