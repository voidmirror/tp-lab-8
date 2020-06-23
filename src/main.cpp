#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <fstream>
#include <string>

using namespace std;

typedef deque<string> prefix;         
const int NPREF = 2;
const int MAXGEN = 1000; 

int main() {
	setlocale(LC_ALL, "Russian");
	int k;
	int ch;
	prefix tmpPref;
	prefix Spref;
	prefix tmpSpref;
	map<prefix, vector<string> > statetab;

	ifstream fin("input.txt");
	if (!fin) return -1;

	string tmpbuff = "";
	for (int i = 0; i < NPREF; i++) {
		fin >> tmpbuff;
		tmpPref.push_back(tmpbuff);
	}
	Spref = tmpPref;
	while (!fin.eof()) {
		tmpbuff = "";
		fin >> tmpbuff;
		statetab[tmpPref].push_back(tmpbuff);
		tmpPref.pop_front();
		tmpPref.push_back(tmpbuff);
	}

	fin.close();

	ofstream fout("output.txt");
	if (!fout) return -1;
	for (int i = 0; i < NPREF; i++) {
		fout << Spref[i] << " ";
	}
	k = NPREF;
	while (k < MAXGEN && Spref != tmpPref) {
		tmpSpref = Spref;
		ch = rand() % statetab[Spref].size();
		fout << statetab[Spref][ch] << " ";
		Spref.pop_front();
		Spref.push_back(statetab[tmpSpref][ch]);
		k++;
		if (k % 9 == 0) fout << "\n";
	}
	fout.close();
	return 0;
}