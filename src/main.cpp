#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; // объем текста на выходе
typedef deque<string> prefixes; // очередь префиксов

int main() {
	srand(time(NULL));
	ifstream fin;
	ofstream fout;

	fin.open("input.txt");
	if (!fin.is_open()) {
		cout << "Input Error" << endl;
		return 1;
	}
	prefixes first;
	string buff = "";
	for (int i = 0; i < NPREF; i++) {
		fin >> buff;
		first.push_back(buff);
	}
	map<prefixes, vector<string> > pref_suff_table; // префикс-суффиксы
	prefixes current = first;
	while (!fin.eof()) {
		fin >> buff;
		pref_suff_table[current].push_back(buff);
		current.pop_front();
		current.push_back(buff);
	}
	fin.close();


	fout.open("output.txt");
	if (!fout.is_open()) {
		cout << "Output Error";
		return 1;
	}
	current = first;
	vector<string>* suffixes = nullptr;
	suffixes = &pref_suff_table[first];
	for (string str : first) {
		fout << str << " ";
	}

	int currentSize = NPREF;
	while ((!suffixes->empty()) && currentSize < MAXGEN) {
		buff = suffixes->at(rand() % suffixes->size());
		fout << buff << " ";
		current.pop_front();
		current.push_back(buff);
		currentSize++;
		suffixes = &pref_suff_table[current];
	}
	fout.close();

	cout << "DONE" << endl;
}