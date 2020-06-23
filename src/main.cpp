#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <time.h>
#include <deque>
#include <vector>


typedef std::deque<std::string> Prefix;
const int NPREF = 2;
const int MAXGEN = 1000;

const std::string INFILE = "in.txt";
const std::string OUTFILE = "out.txt";


std::map<Prefix, std::vector<std::string>> makePrefix(std::string filename);
void generateText(std::string filename, std::map<Prefix, std::vector<std::string>> statetab);


int main() {
	std::map<Prefix, std::vector<std::string>> statetab = makePrefix(INFILE);
	generateText(OUTFILE, statetab);
}

std::map<Prefix, std::vector<std::string>> makePrefix(std::string filename) {
	Prefix prefix;
	std::map<Prefix, std::vector<std::string>> statetab;
	std::ifstream inFile(filename);
	std::string word;

	if (!inFile.is_open()) {
		exit(0);
	}

	for (int i = 0; i < NPREF; i++) {
		std::string word;
		inFile >> word;
		prefix.push_back(word);
	}
	while (inFile >> word) {
		statetab[prefix].push_back(word);
		prefix.pop_front();
		prefix.push_back(word);
	}

	inFile.close();
	return statetab;
}

void generateText(std::string filename, std::map<Prefix, std::vector<std::string>> statetab) {
	std::ofstream out(filename);
	Prefix prefix;
	srand(time(NULL));

	prefix = statetab.begin()->first;  
	for (std::string word : prefix) {
		out << word;
	}
	for (int i = NPREF; i <= MAXGEN; i++) {
		if (!statetab[prefix].empty()) {
			int suff_index = rand() % (int)statetab[prefix].size(); 
			std::string suffix = statetab[prefix][suff_index];
			out << suffix << " ";
			prefix.pop_front();
			prefix.push_back(suffix);
		}
	}

	out.close();
}