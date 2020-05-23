#ifndef TEXTGENERATOR_H
#define TEXTGENERATOR_H

#include<map>
#include<deque>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class TextGenerator
{
    public:
        TextGenerator();
        void readFile(string filename);
        string genText();
        void printTable() const;
        void genTextIntoFile(string filename);
    protected:

    private:
        deque<string> txtEntryPoint;
        deque<string> prefix; // очередь префиксов
        map<deque<string>, vector<string> > statetab; // префикс-суффиксы
        const int NPREF=2; // количество слов в префиксе
        const int MAXGEN=1000; //объем текста на выходе
        void fillStateTab(string text);
        vector<string> split(const string &s, char delim);
        string giveWordForCurPrefix();
};

#endif // TEXTGENERATOR_H
