#include <iostream>  
#include <map>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <time.h>

using namespace std;

typedef deque<string> prefix;          // очередь префиксов
map<prefix, vector<string> > statetab; // префикс-суффиксы

const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 10000; //объем текста на выходе
const int LINESIZE = 10; // длина строки

int main() {
	string inputFilename = "input.txt";
	ifstream in(inputFilename);
	if (!in) {
		cout << "Unable to open file " << inputFilename << '\n';
		exit(0);
	}
	prefix pr;
	for (int i = 0; i < NPREF; i++) {
		string word;
		in >> word;
		pr.push_back(word);
	}
	prefix initial = pr;
	string word;
	while (in >> word) {
		statetab[pr].push_back(word);
		pr.pop_front();
		pr.push_back(word);
	}
	in.close();
	string outputFilename = "output.txt";
	ofstream out(outputFilename);
	for (string& word : initial) {
		out << word << " ";
	}
	srand(time(0));
	for (int wordCount = NPREF; wordCount <= MAXGEN && statetab[initial].size(); wordCount++) {
		int index = rand() % (int)statetab[initial].size();
		//cout << statetab[initial].size() << '\n';
		string word = statetab[initial][index];
		out << word << " ";
		if (wordCount % LINESIZE == 0) {
			out << '\n';
		}
		initial.pop_front();
		initial.push_back(word);
	}
	out.close();
}