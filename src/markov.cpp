#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include<string>
#include<ctime>

using namespace std;

const int NPREF = 2;
const int MAXGEN = 1000;

int main() {
    map<deque<string>, vector<string>> statetab;
    deque<string> next;
    deque<string> start;
    ifstream in("input.txt");
    string str;
    for (int i = 0; i < NPREF; i++) {
        in >> str;
        next.push_back(str);
    }
    start = next;
    while (in >> str) {
        statetab[next].push_back(str);
        next.pop_front();
        next.push_back(str);
    }
    in.close();

    ofstream out("output.txt");
    for (int i = 0; i < NPREF; i++) {
        out << start[i] << " ";
    }
    map<deque<string>, vector<string>>::iterator it;
    next = start;
    string suff;
    srand(time(0));
    for (int i = 0; i < MAXGEN; i++)
    {
        it = statetab.find(next);
        if (it != statetab.end())
        {
            suff = it->second[rand() % (it->second).size()];
            out << suff << " ";
            next.pop_front();
            next.push_back(suff);
        }
    }
    return 0;
}