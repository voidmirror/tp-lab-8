//
// Created by Оксана on 21.05.2020.
//

#ifndef TASK1_TASK1_H
#define TASK1_TASK1_H

#include <deque>
#include <string>
#include <vector>
#include <map>
#include <time.h>

using namespace std;

typedef deque<string> prefix;          // очередь префиксов

const int NPREF=2; // количество слов в префиксе
const int MAXGEN=1000; //объем текста на выходе

int generateText(const char* inputFile, const char* outputFile);



#endif //TASK1_TASK1_H
