#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include <iostream>
#include <map>
#include <string>
#include <deque>
#include <vector>
#include <regex>
#include <fstream>


typedef std::vector <std::string> prefix;
typedef std::vector <std::string> suffix; 


class TextGenerator
{
private:
    unsigned int NPREF=2; 
    const int MAXGEN=200;	
    prefix start = {"START"};

    std::map < prefix, suffix > stateTable;  

public:
    TextGenerator();
    ~TextGenerator();
    void analysis(std::string text);
    std::string findRandomWord(prefix pr);
    std::string generateStr();
    std::map < prefix, suffix > getStateTable() const;
    void printTable() const;
    std::string readFileAndGenerateText(std::string fname);
};

#endif