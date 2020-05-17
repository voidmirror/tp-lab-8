#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <string>
#include <vector>

using namespace std;

typedef deque<string> prefix;
const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе

int main()
{
	map<prefix, vector<string> > statetab;
	ifstream input("input.txt");
	prefix first, second;
	string s;

	if (!input.is_open()) {
		cout << "Can't open input file" << endl;
		exit(0);
	}
	else {
		for (auto i = 0; i < NPREF; i++) {
			input >> s;
			first.push_back(s);
		}

		second = first;

		while (input >> s) {
			statetab[first].push_back(s);
			first.pop_front();
			first.push_back(s);
		}

		input.close();
		ofstream output("output.txt");

		first = second;

		while (!second.empty()) {
			output << second.front() << ' ';
			second.pop_front();
		}
		for (auto i = 0; i < MAXGEN; i++) {
			if (statetab[first].empty()) {
				break;
			}
			int number = rand() % statetab[first].size();
			output << statetab[first][number] << ' ';
			first.push_back(statetab[first][number]);
			first.pop_front();
		}
	output.close();
	}
}