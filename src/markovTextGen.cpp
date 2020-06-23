#include "markovTextGen.h"
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

void markovTextGen(int prefWords, int wordsGen, const string& inputFile, const string& outputFile) {
	typedef deque<string> prefix;
	ifstream fIn(inputFile);
	map<prefix, vector<string>> statetab;

	string wordRead;
	prefix firstPrefix;

	// сохранение первого префикса
	for (int i = 0; i < prefWords; i++) {
		fIn >> wordRead;
		firstPrefix.push_back(wordRead);
	}

	// создание таблицы префиксов
	prefix curPrefix = firstPrefix;
	while (!fIn.eof()) {
		fIn >> wordRead;
		statetab[curPrefix].push_back(wordRead);
		curPrefix.pop_front();
		curPrefix.push_back(wordRead);
	}
	fIn.close();

	// генерация текста
	srand(time(nullptr));
	curPrefix = firstPrefix;
	ofstream fOut(outputFile);
	
	while (!firstPrefix.empty()) {
		fOut << firstPrefix.front() << " ";
		firstPrefix.pop_front();
	}

	string nextWord;
	for (int i = 0; i < wordsGen; i++) {
		auto postfVectorIt = statetab.find(curPrefix);
		if (postfVectorIt == statetab.end()) {
			break;
		}
		nextWord = (*postfVectorIt).second[rand() % (*postfVectorIt).second.size()];
		fOut << nextWord << " ";
		curPrefix.pop_front();
		curPrefix.push_back(nextWord);
	}

	fOut.close();
}