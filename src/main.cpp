#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>
#include <time.h>
using namespace std;

typedef deque<string> prefix; 
const int NPREF = 2; 
const int MAXGEN = 1000; 
const int strLenOut = 15;


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	ifstream file;
	file.open("input.txt");
	prefix startPref, curPref;
	map<prefix, vector<string> > statetab;
	string word;
	if (file.is_open()) {
		
		for (int i = 0; i < NPREF; i++) {
			file >> word;
			curPref.push_back(word); 
		}
		startPref = curPref;

		while (file >> word) {
			statetab[curPref].push_back(word); 
			curPref.pop_front();
			curPref.push_back(word); 
		}
		file.close();

		ofstream fout;
		fout.open("output.txt");

		for (int i = 0; i < NPREF; i++)
		{
			fout << startPref[i] << ' ';
		}
		curPref = startPref;

		for (int i = NPREF; i < MAXGEN; i++) { 

			if (statetab[curPref].empty()) 
				break; 

			int suffixKey = rand() % statetab[curPref].size(); 
			fout << statetab[curPref][suffixKey] << " "; 
			if (i % strLenOut == 0) {
				fout << endl;
			}
			curPref.push_back(statetab[curPref][suffixKey]);
			curPref.pop_front();
		}

		fout.close();
		return 0;
	}
	else {
		cout << "Error opening a file" << endl;
		return -1;
	}
}