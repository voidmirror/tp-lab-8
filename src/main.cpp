#include <iostream>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include <cstdlib>
#include <ctime>

typedef std::deque<std::string> prefix;  // очередь префиксов

const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе
const int MAXLENLINE = 10; // максимальная длина строки в выходном файле


int main() {	
	std::map<prefix, std::vector<std::string> > statetab; // префикс-суффиксы

	std::ifstream inFile("../file/data.txt");
	if (inFile.is_open() == false) {
		std::cout << "Unable to open input file" << std::endl;
		return 1;
	}
	
	//create statetab
	std::string word;
	prefix pref;

	for (int i = 0; i < NPREF; i++) {
		inFile >> word;
		pref.push_back(word);
	}

	inFile >> word;
	statetab[pref] = { word };

	while (inFile.eof() == false) {
		pref.pop_front();
		pref.push_back(word);

		inFile >> word;
		statetab[pref].push_back(word);
	}

	inFile.close();
	
	//generate text
	srand(time(0));

	std::ofstream outFile("../file/output.txt");
	if (outFile.is_open() == false) {
		std::cout << "Unable to open output file" << std::endl;
		return 1;
	}
	
	pref = statetab.begin()->first;
	for (std::string item : pref) {
		outFile << item << ' ';
	}

	for (int i = NPREF; i <= MAXGEN; i++) {
		
		std::string word = statetab[pref][rand() % statetab[pref].size()];
		outFile << word << ' ';

		if (i % MAXLENLINE == 0) {
			outFile << '\n';
		}

		pref.pop_front();
		pref.push_back(word);

		if (statetab[pref].empty()) {
			break;
		}
	}
	outFile.close();	
}