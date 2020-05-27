#pragma once
#include <iostream>
#include <map>
#include <deque>
#include <string>
#include <vector>
#include <fstream>

static const int NPREF = 2;
static const int MAXGEN = 1000;

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;
class Generator {
private:
    statetab prefTable;
    prefix prefixes;
    prefix initPref;
    std::string fileName;
    std::string outputName;
public:
    Generator(std::string fileName, std::string outputName);
    void dataGen();
    void textGen();
    static void test();
};