#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

#define NPREF 2
#define MAXGEN  1000
using namespace std;
typedef deque<string> pref;

int main() {
	srand(time(0));
	vector<string> suffix;
	map <pref, vector<string>> statetab;

	ifstream file("./in.txt");
	if (!file.is_open()) {
		cout << "cant open file in.txt";
		return 0;
	}

	string word;
	pref begin_prefix, prefix;

	for (int i = 0; i < NPREF; i++) {
		file >> word;
		prefix.push_back(word);  // (word1, word2):
	}

	begin_prefix = prefix;

	while (!file.eof()) {
		file >> word;
		if (statetab.find(prefix) == statetab.end()) {
			suffix.push_back(word);  
			statetab.emplace(prefix, suffix); // new record in statetab "(word2, word3): [word4] "
			suffix.clear();
		}
		else {
			statetab[prefix].push_back(word); // add to suffixe new word: "(word1, word2): [word3]"
		}
		prefix.pop_front(); 
		prefix.push_back(word); // prefix: was (word1, word2), now (word2, word3)
	}
	file.close();

	ofstream output("./out.txt");
	prefix = begin_prefix;
	output << begin_prefix[0] << ' ' << begin_prefix[1] << ' '; //first prefix from begin of text
	int len_string = 0;

	for (int i = 0; i < MAXGEN; i++) {
		if (statetab.find(prefix) != statetab.end()) {
			int random_suffix = rand() % statetab.find(prefix)->second.size();
			output << statetab[prefix][random_suffix] << ' '; //echo random suffix from lsit
			prefix.push_back(statetab[prefix][random_suffix]);
			prefix.pop_front(); //update prefix

			len_string += statetab[prefix][random_suffix].size; //new line
			if (len_string > 70) {
				output << endl; len_string = 0;
			}
		}
	}
	output.close();

	return 0;
}