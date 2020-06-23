#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
using namespace std;
typedef deque<string> prefix;
map<prefix, vector<string> > statetab;

int main() {
	const int NPREF = 2;
	const int MAXGEN = 1000;

	prefix pref, startingPref;

	string phrase;
	ifstream fin("myFile.txt");
	ofstream outFail("out.txt");

	

	if (!fin.is_open()) {
		cout << "Open file error!" << endl;	
	}
	else
	{
		cout << "File was opened!" << endl;
		for (int i = 0; i < NPREF; i++) {
			fin >> phrase;
			pref.push_back(phrase);
		}
		startingPref = pref;

		while (fin >> phrase) {
			statetab[pref].push_back(phrase);
			pref.pop_front();
			pref.push_back(phrase);
		}


		fin.close();

		pref = startingPref;
		for (int i = 0; i < NPREF; i++) {
			outFail << startingPref[i] << " ";
		}

		for (int i = 0; i < MAXGEN; i++) {
			if (statetab[pref].empty()) {
				break;
			}
			int id = rand() % statetab[pref].size();
			string postfix = statetab[pref][id];
			outFail << postfix << " ";
			if (i % 5 == 0) {
				outFail << endl;
			}
			pref.push_back(postfix);
			pref.pop_front();
		}

		outFail.close();


		return 0;
	}
}