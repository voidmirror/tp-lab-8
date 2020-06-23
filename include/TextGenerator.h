#ifndef MARKOV_TEXTGENERATOR_H
#define MARKOV_TEXTGENERATOR_H

#include <iostream>
#include <map>
#include <deque>
#include <string>
#include <vector>
#include <fstream>

static const size_t NPREF = 2;
static const size_t MAXGEN = 300;

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

class TextGenerator {

private:
    statetab prefixTable;

    prefix prefixes;
    prefix initialPrefixes;

    std::string inputFileName;
    std::string outputFileName;

public:

    TextGenerator(std::string inputFileName, std::string outputFileName);

    void generateData();

    void generateText();

    static void testProcessing();
};


#endif //MARKOV_TEXTGENERATOR_H
