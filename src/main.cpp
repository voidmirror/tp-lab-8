//
// Created by Илья Соловьёв on 23.05.2020.
//

#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <random>
#include <vector>

typedef std::deque<std::string> prefix;

const int NPREF = 3; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе

int read(const char *filename,
         std::map<prefix, std::vector<std::string> > &statetab) {
    prefix aPrefix;
    std::ifstream in_file(filename);
    if (!in_file.is_open()) {
        std::cout << "Cannot open input file" << std::endl;
        return 1;
    }
    std::string aTemp;
    for (auto i = 0; i < NPREF; i++) {
        in_file >> aTemp;
        aPrefix.push_back(aTemp);
    }
    while (in_file >> aTemp) {
        statetab[aPrefix].push_back(aTemp);
        aPrefix.pop_front();
        aPrefix.push_back(aTemp);
    }
    in_file.close();
    return 0;
}

int generate(const char *in_filename,
             const char *out_filename,
             std::map<prefix, std::vector<std::string> > &statetab) {
    std::ifstream in_file(in_filename);
    if (!in_file.is_open()) {
        std::cout << "Cannot open input file" << std::endl;
        return 1;
    }
    prefix aPrefix;
    std::string aTemp;
    for (auto i = 0; i < NPREF; i++) {
        in_file >> aTemp;
        aPrefix.push_back(aTemp);
    }
    in_file.close();
    std::ofstream out_file(out_filename);
    if (!out_file.is_open()) {
        std::cout << "Cannot open output file";
        return 1;
    }
    for (const auto& word : aPrefix) {
        out_file << word << " ";
    }
    for (auto i = NPREF; i < MAXGEN; i++) {
        auto iter = statetab.find(aPrefix);
        if (iter != statetab.end()) {
            std::default_random_engine gen;
            aTemp = iter->second[gen() % (iter->second).size()];
            out_file << aTemp << " ";
            aPrefix.pop_front();
            aPrefix.push_back(aTemp);
        }
    }
    out_file.close();
    return 0;
}

int main() {
    std::map<prefix, std::vector<std::string>> statetab;
    read("../src/input.txt", statetab);
    generate("../src/input.txt", "../src/output.txt", statetab);
    return 0;
}