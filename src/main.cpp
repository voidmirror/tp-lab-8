#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <fstream>
#include <time.h>
const int NPREF = 2; //num of words in prefix
const int MAXGEN = 1000; // size of final text
using namespace std;

typedef deque<string> prefix; 

int main() {
	setlocale(LC_ALL, "Russian");
	ifstream fin("input.txt");
	srand(time(NULL));
	map<prefix, vector<string> > statetab; //prefix-suff

	string buffer;
	prefix curPrefix;
	for (int i = 0; i < NPREF; i++) {
		fin >> buffer;
		curPrefix.push_back(buffer);
	}
	prefix tempPrefix = curPrefix;

	while (fin >> buffer) {
		statetab[curPrefix].push_back(buffer);
		curPrefix.pop_front();
		curPrefix.push_back(buffer);
	}

	fin.close();

	curPrefix = tempPrefix;

	ofstream fout("output.txt");
	for (int i = 0; i < curPrefix.size(); i++)
		fout << curPrefix[i] << " ";

	vector<int> lengths = { 6, 7, 8, 9 };

	int k = rand() % 4;
	int num_in_line = NPREF;

	for (int i = NPREF; i < MAXGEN; i++) {
		if (!statetab[curPrefix].empty()) {
			int index = rand() % statetab[curPrefix].size();
			fout << statetab[curPrefix][index] << " ";
			num_in_line++;
			if (num_in_line == lengths[k]) {
				fout << "\n";
				num_in_line = 0;
				k = rand() % 4;
			}
			curPrefix.pop_front();
			curPrefix.push_back(statetab[curPrefix][index]);
		}
		else
			break;
	}

	fout.close();
	return 1;
}