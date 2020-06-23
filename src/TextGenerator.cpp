//
// Created by artem on 24.05.2020.
//

#include "TextGenerator.h"

TextGenerator::TextGenerator(std::string inputFileName, std::string outputFileName) {
    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;
}

void TextGenerator::generateData() {
    std::string str;
    std::ifstream file(inputFileName);

    for (int i = 0; i < NPREF; i++) {
        file >> str;
        initialPrefixes.push_back(str);
    }

    prefixes = initialPrefixes;
    while (file >> str) {
        prefixTable[prefixes].push_back(str);
        prefixes.pop_front();
        prefixes.push_back(str);
    }
    file.close();
}

void TextGenerator::generateText() {
    std::string outputText = "";

    for (int i = 0; i < NPREF; i++) {
        outputText.append(initialPrefixes[i]).append(" ");
    }

    prefixes = initialPrefixes;
    for (int i = 0; i < MAXGEN; i++) {

        if (prefixTable.find(prefixes) != prefixTable.end()) {

            std::string current = prefixTable
                    .find(prefixes)->second[rand() % prefixTable.find(prefixes)->second.size()];
            outputText.append(current).append(" ");

            prefixes.pop_front();
            prefixes.push_back(current);
        }
    }

    std::ofstream file(outputFileName);
    file << outputText;
    file.close();
}

void TextGenerator::testProcessing() {
    auto textGenerator = TextGenerator("input.txt", "output.txt");
    textGenerator.generateData();
    textGenerator.generateText();
}

