//
// Created by aklen on 16.05.2020.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include <ctime>
using namespace std;

const int NPREF=2;
const int MAXGEN=400;


typedef deque<string> prefix;


bool build(const string &input_path, map<prefix,vector<string>> &statetab){
    prefix pref;
    ifstream in_file(input_path);

    if(!in_file.is_open()){
        return false;
    }

    string tmp;
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
    return true;
}


void newText(const string input_path, const string output_path, map<prefix,vector<string>> &statetab){
    ifstream in_file(input_path);
    if(!in_file.is_open()){
        cout<<"Can not open input file"<<endl;
        return;
    }

    prefix pref;
    string tmp;
    for(int i = 0; i<NPREF; i++){
        in_file >> tmp;
        pref.push_back(tmp);
    }
    in_file.close();

    ofstream out_file(output_path);
    if(!out_file.is_open()){
        cout<<"Can not open output file"<<endl;
        return;
    }

    for(auto word: pref){
        out_file << word << " ";
    }

    for(int i=NPREF; i<MAXGEN; i++){
        auto it = statetab.find(pref);
        if(it != statetab.end()){
            tmp = it->second[rand() % (it->second.size())];
            out_file << tmp << " ";
            pref.pop_front();
            pref.push_back(tmp);
        }
    }

    out_file.close();
    cout << "New text was generated successfully"<<endl;
}



int main(){
    srand(time(0));
    map<prefix,vector<string>> statetab;
    if(build("../test/input.txt",statetab))
        newText("../test/input.txt","../test/output.txt",statetab);
    return 0;
}

