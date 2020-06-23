#include <funcs.h>
#include <fstream>
#include <random>
#include "config.h"

void makeTable(ifstream &input, Prefix &startPrefix, map<Prefix, vector<string>> & statetab) {
    string word;
    Prefix prefix;

    for (int i = 0; i < PREFSIZE; ++i) {
        input >> word;
        extendTable(prefix, word, statetab);
    }

    startPrefix = prefix;

    while (input >> word) {
        extendTable(prefix, word, statetab);
    }
}

void extendTable(Prefix &prefix, const string &word,  map<Prefix, vector<string>> &statetab) {
    if (prefix.size() == PREFSIZE) {
        statetab[prefix].push_back(word);
        prefix.pop_front();
    }
    prefix.push_back(word);
}

void generateText(ofstream &output, Prefix &startPrefix, map<Prefix, vector<string>> &statetab) {
    Prefix prefix;

    map<Prefix, vector<string>>::iterator nextPrefix;
    string suffixWord;

    for (const string& startWord : startPrefix) {
        output << startWord << " ";
    }

    prefix = startPrefix;

    for (int i = 0; i < TEXTSIZE; ++i) {
        nextPrefix = statetab.find(prefix);
        if (nextPrefix != statetab.end()) {
            suffixWord = nextPrefix->second[getRandInt(0, nextPrefix->second.size() - 1)];
            output << suffixWord << " ";
            prefix.pop_front();
            prefix.push_back(suffixWord);
        }
    }
}

int getRandInt(int min, int max){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}

