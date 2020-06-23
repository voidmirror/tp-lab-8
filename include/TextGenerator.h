#ifndef LAB8_TEXTGENERATOR_H
#define LAB8_TEXTGENERATOR_H


#define NPREF 2
#define MAXGEN 2000


#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <vector>
#include <map>


class TextGenerator{
private:
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string>> statetab;
public:
    TextGenerator()= default;;
    void generateText(const std::string& inputFileName, const std::string& outputFileName);
};


#endif //LAB8_TEXTGENERATOR_H