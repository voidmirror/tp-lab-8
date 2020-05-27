#include "Generator.h"

Generator::Generator(std::string fileName, std::string outputName) 
{
    this->fileName = fileName;
    this->outputName = outputName;
}
void Generator::textGen() {
    std::string output = "";

    for (int i=0; i <NPREF; i++) {
        output.append(initPref[i]).append(" ");
    }
    prefixes = initPref;
    for (int i = 0; i < MAXGEN; i++) {
        if (prefTable.find(prefixes) != prefTable.end()) {
            std::string current = prefTable
                .find(prefixes)->second[rand() % prefTable.find(prefixes)->second.size()];
            output.append(current).append(" ");
            prefixes.pop_front();
            prefixes.push_back(current);
        }
    }
    std::ofstream file(outputName);
    file << output;
    file.close();
}
void Generator::dataGen() {
    std::string text;
    std::ifstream file(fileName);
    for (int i=0; i <NPREF;i++) 
    {
        file >> text;
        initPref.push_back(text);
    }
    prefixes = initPref;
    while (file >> text) 
    {
        prefTable[prefixes].push_back(text);
        prefixes.pop_front();
        prefixes.push_back(text);
    }
    file.close();
}
void Generator::test() {
    auto textGen = Generator("in.txt", "out.txt");
    textGen.dataGen();
    textGen.textGen();
}

