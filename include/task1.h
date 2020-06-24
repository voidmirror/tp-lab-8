#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <cstdlib>
#include <random>
using namespace std;
typedef deque<string> prefix;

const int NPREF = 1;
const int MAXGEN = 2000;

vector<string> read_text(string);
map<prefix, vector<string>> generate_prefix_table(vector<string>);
string generate_text(vector<string>);
string random_word(vector<string>);