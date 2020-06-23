//
// Created by Mikhail on 21.05.2020.
//

#ifndef TASK1_TASK1_H
#define TASK1_TASK1_H

#include <deque>
#include <string>
#include <vector>
#include <map>

using std::deque;
using std::map;
using std::vector;
using std::string;

typedef deque<string> prefix;          // очередь префиксов


const int NPREF=2; // количество слов в префиксе
const int MAXGEN=1000; //объем текста на выходе

int fillStateTab(const string& inputFile);

int outData(string outputFile);

#endif //TASK1_TASK1_H
