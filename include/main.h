#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <string>
#include <vector>
#include <ctime>

using namespace std;
typedef deque<string> prefix;

const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе