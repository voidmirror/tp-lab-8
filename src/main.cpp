#include <deque>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


int main() {
	typedef deque<string> prefix; //prefix queue
	map<prefix, vector<string>> statetab; //prefix suffixes
	const int NPREF = 2; //number of words in the prefix
	const int MAXGEN = 1000; //output text volume

	prefix pref, init_pref;

	ifstream inpfile("input.txt");
	string word;

	if (inpfile.is_open()) {
		for (int i = 0; i < NPREF; i++) {
			inpfile >> word;
			pref.push_back(word);
		}
		init_pref = pref;
		while (inpfile >> word) {
			statetab[pref].push_back(word);
			pref.pop_front();
			pref.push_back(word);
		}
	}
	else {
		cout << "Can't open a file:(" << endl;
	}
	pref = init_pref;

	ofstream outfile("output.txt");
	outfile << init_pref[0] << ' ' << init_pref[1] << ' ';

	for (int i = 0; i < MAXGEN; i++) {
		int p;
		if (statetab[pref].size() != 0)
			p = rand() % statetab[pref].size();
		else
			continue;
		outfile << statetab[pref][p] << ' ';

		if (i % 5 == 0)
			outfile << endl;

		pref.push_back(statetab[pref][p]);
		pref.pop_front();
	}

	inpfile.close();
	outfile.close();
	return 0;
}