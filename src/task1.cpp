#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;
using Prefix = deque<string>;
const int NPREF = 1;
const int MAXGEN = 100;
int main() {
    srand(time(NULL));
    map<Prefix, vector<string>> stateTab;
    fstream inStream("input.txt");
    fstream outStream("output.txt");
    Prefix prefix(NPREF);
    string word;
    for (auto& x : prefix) {
        inStream >> x;
    }
    while(inStream >> word) {
        stateTab[prefix].push_back(word);
        prefix.pop_front();
        prefix.push_back(word);
    }
    auto item = stateTab.begin();
    std::advance(item, rand() % stateTab.size());
    prefix = item->first;
    for (const auto& x : prefix)
        outStream << x << " ";
    for (int i = 0; i < MAXGEN - NPREF; i++) {
        int n = stateTab[prefix].size();
        if (n == 0)
            break;
        string suf = stateTab[prefix][rand() % n];
        outStream << suf << " ";
        prefix.pop_front();
        prefix.push_back(suf);
    }
    return 0;
}
