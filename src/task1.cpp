//
// Created by Оксана on 21.05.2020.
//
#include <iostream>
#include <fstream>
#include "task1.h"

using namespace std;


int generateText(const char* fileIn, const char* fileOut){

    map <prefix, vector<string> > statetab;

    setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
    ifstream fin(fileIn);// открыли файл для чтения


    if (!fin.is_open()) {
        std::cout << "File was not opened" << std::endl;
        return 0;
    }

    prefix pref;
    string str;

    for (int i = 0; i < NPREF; i++) {
        fin >> str;
        pref.push_back(str);
    }
    prefix tmp = pref;
    while (fin >> str)
    {
        statetab[tmp].push_back(str);
        tmp.pop_front();
        tmp.push_back(str);
    }
    fin.close();


    ofstream fout(fileOut);
    srand(time(0));

    if (!fout.is_open()) {
        std::cout << "File was not opened" << std::endl;
        return 0;
    }

    for (string x : pref) {
        fout << x << " ";
    }
    for (int i = NPREF; i < MAXGEN; i++){
        if (!statetab[pref].empty()){

            int index = rand() % (int)statetab[pref].size();
            fout << statetab[pref][index] << " ";
            pref.push_back(statetab[pref][index]);
            pref.pop_front();
        }
    }
    return 1;
}
