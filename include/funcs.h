#ifndef TEXT_GENERATOR_FUNCS_H
#define TEXT_GENERATOR_FUNCS_H

#include <string>
#include <deque>
#include <vector>
#include <map>

using namespace std;

typedef deque<string> Prefix;

void makeTable(ifstream &input, Prefix &startPrefix, map<Prefix, vector<string>> &);
void extendTable(Prefix &prefix, const string& word, map<Prefix, vector<string>> & statetab);
void generateText(ofstream &output, Prefix &startPrefix, map<Prefix, vector<string>> &statetab);
int getRandInt(int min, int max);

#endif //TEXT_GENERATOR_FUNCS_H
