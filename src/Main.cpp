#include <iostream>
#include <ctime>
#include <vector>
#include <deque>
#include <map>
#include <fstream>

const int NPREF=2;
const int MAXGEN=400;
const std::string inputPath = "input.txt";
const std::string outputPath = "output.txt";


typedef std::deque<std::string> prefix;


int main() {
    
    srand(time(nullptr));
    std::map<prefix,std::vector<std::string>> statetab;

    prefix pref;
    std::string tmp;

    std::ifstream in_file(inputPath);

    for(int i = 0; i<NPREF;i++){
        in_file >> tmp;
        pref.push_back(tmp);
    }

    while(in_file >> tmp){
        statetab[pref].push_back(tmp);
        pref.pop_front();
        pref.push_back(tmp);
    }

    in_file.close();

    std::ifstream in_file2(inputPath);

    prefix pref2;
    std::string tmp2;
    for(int i = 0; i<NPREF; i++){
        in_file2 >> tmp2;
        pref2.push_back(tmp);
    }
    in_file2.close();

    std::ofstream out_file(outputPath);

    for(const auto& word: pref2){
        out_file << word << " ";
    }

    for(int i=NPREF; i<MAXGEN; i++){
        auto it = statetab.find(pref2);
        if(it != statetab.end()){
            tmp2 = it->second[rand() % (it->second.size())];
            out_file << tmp2 << " ";
            pref2.pop_front();
            pref2.push_back(tmp);
        }
    }

    out_file.close();
    return 0;
}