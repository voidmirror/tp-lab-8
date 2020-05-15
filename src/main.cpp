//
//  main.cpp
//  lab8
//
//  Created by Андрей Журавлев on 15.05.2020.
//  Copyright © 2020 Андрей Журавлев. All rights reserved.
//

#include <iostream>
#include <map>
#include <deque>
#include <string>
#include <vector>
#include <fstream>
#include <random>

static const size_t NPREF = 2;
static const size_t MAXGEN = 300;
static const std::string OUTPUT_FILE_NAME = "output.txt";

typedef std::deque<std::string> PrefixType;
typedef std::map<PrefixType, std::vector<std::string>> PrefixTabType;

class TextGenerator {
	PrefixTabType prefixTable;
	PrefixType prefixes;
	PrefixType firstPrefixes;	
	std::string generatedText;
	
public:
	TextGenerator(std::string fileName) {
		std::ifstream file(fileName);
		
		if (!file.is_open()) {
			throw "File does not exist";
		}
		
		std::string str;
		for (int i = 0; i < NPREF; i++) {
			file >> str;
			firstPrefixes.push_back(str);
		}
		
		prefixes = firstPrefixes;
		while (file >> str) {
			prefixTable[prefixes].push_back(str);
			prefixes.pop_front();
			prefixes.push_back(str);
		}
		file.close();
		
		for (int i = 0; i < NPREF; i++) {
			generatedText.append(firstPrefixes[i]).append(" ");
		}
		
		prefixes = firstPrefixes;
		for (int i = 0; i < MAXGEN; i++) {
			auto it = prefixTable.find(prefixes);
			if (it == prefixTable.end()) continue;
			std::string temp = it->second[rand() % it->second.size()];
			generatedText.append(temp).append(" ");
			prefixes.pop_front();
			prefixes.push_back(temp);
		}
	}
	
	std::string getText() {
		return generatedText;
	}
	
	void saveToFile(std::string fileName = OUTPUT_FILE_NAME) {
		std::ofstream file(fileName);
		file << generatedText;
	}
	
};

int main(int argc, const char * argv[]) {
	// insert code here...
	TextGenerator gen("input.txt");
	gen.saveToFile();
	return 0;
}
