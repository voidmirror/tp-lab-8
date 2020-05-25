#pragma once
#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>

const int NPREF = 2;
const int MaXGEN = 1000;
typedef std::deque<std::string> prefix;
typedef unsigned int uint;

void generator();