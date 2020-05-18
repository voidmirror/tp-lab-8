#include "generator.h"

Generator::Generator() {
	table_made = false;
}

Generator::Generator(string filename) {
	ifstream fin;
	string buf1, buf2;
	prefix deq;
	int num;

	fin.open(filename);
	if (fin.is_open()) {
		fin >> buf1 >> buf2;
		s_words.push_back(buf1);
		s_words.push_back(buf2);

		while (!fin.eof()) {
			fin >> buf1 >> buf2 >> num;
			deq.push_back(buf1);
			deq.push_back(buf2);
			vector<string>& lvec = table[deq];
			for (int i = 0; i < num; i++) {
				fin >> buf1;
				lvec.push_back(buf1);
			}
			deq.pop_front();
			deq.pop_front();
		}
		
		fin.close();
	}
	else {
		cout << "File wasn't open" << endl;
	}
	if (!table.empty()) table_made = true;
}

void Generator::makeTable(string filename) {
	ifstream fin;
	string buf;
	prefix deq;

	table.clear();
	table_made = false;

	fin.open(filename);
	if (fin.is_open()) {
		fin >> buf;
		s_words.push_back(buf);
		deq.push_back(buf);
		if (!fin.eof()) {
			fin >> buf;
			s_words.push_back(buf);
			deq.push_back(buf);
			while (!fin.eof()) {
				fin >> buf;
				table[deq].push_back(buf);
				deq.pop_front();
				deq.push_back(buf);
			}
		}
		fin.close();
	}
	else {
		cout << "File wasn't open" << endl;
	}
	if (!table.empty()) table_made = true;
}

int Generator::generateText(string fileout) {
	string buf;
	vector<string> pref;

	if (!table_made) return 1;

	prefix deq;
	deq.push_back(s_words[0]);
	deq.push_back(s_words[1]);

	ofstream fout;
	fout.open(fileout);
	fout << s_words[0] << " " << s_words[1] << " ";
	
	pref = table[deq];
	while (!pref.empty()) {
		buf = pref[rand() % pref.size()];
		fout << buf << " ";
		deq.pop_front();
		deq.push_back(buf);
		pref = table[deq];
	}

	fout.close();
	return 0;
}

int Generator::printTableTo(string fileout) {
	if (!table_made) return 1;
	if (fileout == "") {
		cout << s_words[0] << " " << s_words[1] << endl;
		for (auto& item : table) {
			for (auto elem : item.first) {
				cout << elem << " ";
			}
			cout << endl;
			for (auto& itm : item.second) {
				cout << itm << " ";
			}
			cout << endl;
		}
	}
	else {
		ofstream fout;
		fout.open(fileout);
		fout << s_words[0] << " " << s_words[1] << endl;
		for (auto& item : table) {
			for (auto elem : item.first) {
				fout << elem << " ";
			}
			fout << endl;
			fout << item.second.size() << " ";
			for (auto& itm : item.second) {
				fout << itm << " ";
			}
			fout << endl;
		}
		fout.close();
	}
}
