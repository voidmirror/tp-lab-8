#pragma once
#include <map>
#include <deque>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <random>

using namespace std;

typedef deque<string> prefix;

class Generator {
private:
	bool table_made;
	vector<string> s_words;
	map<prefix, vector<string>> table;
public:
	Generator();
	Generator(string filename); // reading a table from filename
	void makeTable(string filename);
	int generateText(string fileout);
	int printTableTo(string fileout = ""); // defaul in cout
};