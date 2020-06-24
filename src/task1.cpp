#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <ctime>

using namespace std;

typedef deque<string> prefix;

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	map<prefix, vector<string> > statetab;
	prefix first, second;
	string word;
	ifstream input("input.txt");
	if (input.is_open()) {
		for (size_t i = 0; i < NPREF; i++) {
			input >> word;
			first.push_back(word);
		}
		second = first;
		while (input >> word) {
			statetab[second].push_back(word);
			second.pop_front();
			second.push_back(word);
		}
		input.close();
		ofstream output("output.txt");
		if (output.is_open()) {
			for(size_t i = 0; i < first.size(); i++){
				output << first[i] << " ";
			}
			for (size_t i = 0; i < MAXGEN; i++) {
				if (statetab[first].empty()) {
					break;
				}
				int suffixNumber = rand() % statetab[first].size();
				output << statetab[first][suffixNumber] << " ";
				first.push_back(statetab[first][suffixNumber]);
				first.pop_front();
				if (i % 10 == 0) {
					output << endl;
				}
			}
		}
		else {
			cout << "Error of opening input file" << endl;
			return 0;
		}
		output.close();
	}
	else {
		cout << "Error of opening input file" << endl;
		return 0;
	}
	return 0;
}