//
// Created by Илья on 017 17.05.20.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include <map>
#include <string>
#include <vector>
#include <deque>

using std::string;
using std::vector;
using std::deque;
using std::map;
using std::ifstream;
using std::ofstream;


typedef deque<string> Prefix;
const int NPREF=2;
const int MAXGEN=1000;
const int LINE_LEN=10;  // number of words on the line of file with generated text


map<Prefix, vector<string>> make_prefixes(string filename){
    map<Prefix, vector<string>> statetab;
    ifstream in(filename);
    Prefix prefix;
    string word;

    // initial prefix
    for (int i = 0; i < NPREF; i++) {
        string word;
        in >> word;
        prefix.push_back(word);
    }

    while (in >> word) {
        statetab[prefix].push_back(word);
        prefix.pop_front();
        prefix.push_back(word);
    }
    in.close();
    return statetab;
}


void generate_write_text(string filename, map<Prefix, vector<string>> statetab){
    ofstream out(filename);
    srand(time(0));
    Prefix prefix;
    prefix = statetab.begin()->first;  // get initial prefix
    for(string word : prefix){
        out << word;
    }
    for (int i = NPREF; i <= MAXGEN; i++) {
        if (!statetab[prefix].empty()){
            int suff_index = rand() % (int)statetab[prefix].size();  // choose random suffix
            string suffix = statetab[prefix][suff_index];
            out << suffix << " ";
            if (i % LINE_LEN == 0) {
                out << std::endl;
            }
            prefix.pop_front();
            prefix.push_back(suffix);
        }
    }
    out.close();
}


int main(){
    auto statetab = make_prefixes("in.txt");
    generate_write_text("out.txt", statetab);
}

