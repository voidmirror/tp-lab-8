#include <map>
#include <deque>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef deque<string> prefix;  // prefix queue
map<prefix, vector<string>> statetab; // prefix-suffix

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");

	string word;
	prefix pref, start_pref;
	ifstream input("input.txt");
	ofstream output("output.txt");

	if (!input.is_open()) {
		cout << "File cannot be opened!" << endl;
		return 1;
	}
	
	for (int i = 0; i < NPREF; i++) {
		input >> word;
		pref.push_back(word);
	}

	start_pref = pref;

	while (input >> word) {
		statetab[pref].push_back(word);
		pref.pop_front();
		pref.push_back(word);
	}
	
	input.close();
	pref = start_pref;

	for (int i = 0; i < NPREF; i++) {
		output << start_pref[i] << " ";
	}
	for (int i = 0; i < MAXGEN; i++) {
		if (statetab[pref].empty()) {
			break;
		}
		int index = rand() % statetab[pref].size();
		string postfix = statetab[pref][index];
		output << postfix << " ";
		if (i % 5 == 0) {
			output << endl;
		}
		pref.push_back(postfix);
		pref.pop_front();
	}
	cout << "Text was successfully generated!";
	output.close();
	return 0;
}

