//
//  TextGenerator.cpp
//  TextGenerator
//
//  Created by Олеся Мартынюк on 18.05.2020.
//  Copyright © 2020 Olesia Martinyuk. All rights reserved.
//

#include "TextGenerator.h"
#include <iostream>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <random>

TextGeterator::TextGeterator() {
    generatedText = "";
    prefix prefixQueue = {};
    this->statetab = {};
    std::string s;
    std::ifstream file(this->inputFilename);
    while(file >> s){
        if (prefixQueue.size() < NPREF)
            prefixQueue.push_back(s);
        else {
            statetab[prefixQueue].push_back(s);
            prefixQueue.pop_front();
            prefixQueue.push_back(s);
        }
    }
}

void TextGeterator::generateText(){
    srand(static_cast<unsigned int>(time(nullptr)));
    std::string s;
    std::ifstream file(this->inputFilename);
    prefix currentPrefix;
    for (int i = 0; i < NPREF; i++) {
        file >> s;
        currentPrefix.push_back(s);
        this->generatedText += s + " ";
    }
    for (int i = 0; i < MAXGEN; i++) {
        if (statetab.find(currentPrefix) != statetab.end()){
            auto value = statetab.find(currentPrefix)->second;
            int index = rand() % value.size();
            this->generatedText += value[index] + " ";
            currentPrefix.pop_front();
            currentPrefix.push_back(value[index]);
        }
    }
}

void TextGeterator::saveText(){
    std::ofstream out(this->outputFilename);
    out << this->generatedText;
    out.close();
}
