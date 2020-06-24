#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

typedef deque<string> prefix;

class Generator {
private:
	map<prefix, vector<string>> statetab;
	prefix initialPrefix;
	size_t NPREF = 2;
	size_t MAXGEN = 1000;

public:
	void inputData(ifstream& input);
	void generate(ofstream& output);
};

#endif
