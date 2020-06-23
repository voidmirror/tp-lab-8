#include "TextGenerator.h"


void TextGenerator::generateText(const std::string& inputFileName, const std::string& outputFileName)
{
    srand((unsigned) time(0));

    prefix prefixesDeque = {};
    prefix tempPrefix = {};

    this->statetab = {};

    std::string resultString;
    std::string tempString;

    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    while (inputFile >> tempString)
    {

        if (prefixesDeque.size() < NPREF)
            prefixesDeque.push_back(tempString);

        else
        {
            this->statetab[prefixesDeque].push_back(tempString);
            prefixesDeque.pop_front();
            prefixesDeque.push_back(tempString);
        }

    }

    tempString = "";
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    for (int i = 0; i < NPREF; i++)
    {
        inputFile >> tempString;
        tempPrefix.push_back(tempString);
        resultString += tempString = " ";
    }

    for (int i = 0; i < MAXGEN; i++)
    {
        if (this->statetab.find(tempPrefix) != this->statetab.end())
        {
            auto pairPrefixSuffix = this->statetab.find(tempPrefix)->second;
            int pairIndex = rand() % pairPrefixSuffix.size();

            resultString += pairPrefixSuffix[pairIndex] + " ";
            tempPrefix.pop_front();
            tempPrefix.push_back(pairPrefixSuffix[pairIndex]);
        }
    }

    outputFile << resultString;
    outputFile.close();

}

