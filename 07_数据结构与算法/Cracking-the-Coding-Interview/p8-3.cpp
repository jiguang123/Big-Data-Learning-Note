// 8.3 Design a data structure to simulate a musical jukebox.
#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class JukeBox {
public:
	JukeBox() {};
	
	void start() {
		work = new thread(workThread, this);
	};

	void addSong(vector<int> &song) {
		songs.push_back(song);
	}
	
	void orderSong(int id) {
		if (id < 0 || id > (int)songs.size() - 1) {
			return;
		}
		song_list.push(id);
	}

	friend void workThread(JukeBox *);

	~JukeBox() {
		while (!song_list.empty()) {
			song_list.pop();
		}
		size_t i;
		for (i = 0; i < songs.size(); ++i) {
			songs[i].clear();
		}
		songs.clear();
		work->detach();
		delete work;
	};
private:
	queue<int> song_list;
	vector<vector<int> > songs;
	thread *work;
};

void workThread(JukeBox *jb) {
	size_t i;
	while (true) {
		if (!jb->song_list.empty()) {
			for (i = 0; i < jb->songs[jb->song_list.front()].size(); ++i) {
				cout << jb->songs[jb->song_list.front()][i] << ' ';
			}
			cout << endl;
			jb->song_list.pop();
		}
	}
};

int main()
{
	JukeBox *jb;
	string cmd;
	int id;
	int i, n;
	vector<int> song;

	jb = new JukeBox();
	jb->start();
	while (cin >> cmd) {
		if (cmd == "add") {
			cin >> n;
			song.resize(n);
			for (i = 0; i < n; ++i) {
				cin >> song[i];
			}
			jb->addSong(song);
		} else if (cmd == "order") {
			cin >> id;
			jb->orderSong(id);
		} else if (cmd == "end") {
			break;
		}
	}
	delete jb;

	return 0;
}