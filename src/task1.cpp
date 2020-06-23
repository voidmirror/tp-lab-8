//
// Created by Mikhail on 21.05.2020.
//

#include <task1.h>
#include <fstream>

using std::ifstream;
using std::ofstream;

#define add push_back

map<prefix, vector<string> > statetab; // префикс-суффиксы
prefix pref;

int fillStateTab(const string& inputFile) {
    ifstream in(inputFile);

    if(!in.is_open()) {
        return 0;
    }

    for (int i = 0; i < NPREF; i++) {
        if (in.eof()) {
            return 0;
        }
        string buf;
        in >> buf;
        pref.add(buf);
    }

    prefix tmp = pref;

    while (!in.eof()) {
        string buf;
        in >> buf;
        statetab[tmp].add(buf);
        tmp.pop_front();
        tmp.add(buf);
    }

    in.close();
    return 1;
}

int outData(string outputFile) {
    ofstream out(outputFile);

    if (!out.is_open()) {
        return 0;
    }

    for(auto &x: pref) {
        out << x << ' ';
    }

    for (int i = 0; i < MAXGEN; i++) {
        auto jt = statetab.find(pref);
        if (jt == statetab.end()) continue;
        string buf = jt->second[rand() % jt->second.size()];
        out << buf << ' ';
        pref.pop_front();
        pref.add(buf);
    }
    return 1;
}
