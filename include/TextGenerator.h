//
//  TextGenerator.h
//  TextGenerator
//
//  Created by Олеся Мартынюк on 18.05.2020.
//  Copyright © 2020 Olesia Martinyuk. All rights reserved.
//

#ifndef TextGenerator_h
#define TextGenerator_h

#include <stdio.h>
#include <deque>
#include <fstream>
#include <vector>
#include <string>
#include <map>

typedef std::deque<std::string> prefix; // очередь префиксов

const int NPREF=2; // количество слов в префиксе
const int MAXGEN=1000; //объем текста на выходе

class TextGeterator {
private:
    std::string generatedText;
    std::map<prefix, std::vector<std::string>> statetab; // префикс-суффиксы
    std::string inputFilename = "input.txt";
    std::string outputFilename = "output.txt";
public:
    TextGeterator();
    void generateText();
    void saveText();
};

#endif /* TextGenerator_h */
