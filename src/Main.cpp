#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "TextGenerator.h"

const std::string c_inputFileName = "input.txt";
const std::string c_outputFileName = "output.txt";

void Split(std::string &str, char separator, std::vector<std::string> *resultSubstrings);
std::string Join(std::vector<std::string> substrings, char separator);

int32_t main()
{
    std::vector<std::string> words;

    std::ifstream streamReader(c_inputFileName);
    std::string str;
    std::getline(streamReader, str);
    while (str != "")
    {
        Split(str, ' ', &words);
        std::getline(streamReader, str);
    }
    streamReader.close();

    text_seed_t textSeed = TextGenerator::CreateTextSeed(words);

    std::ofstream streamWriter(c_outputFileName);
    streamWriter << Join(TextGenerator::GenerateText(textSeed), ' ') << std::endl;
    streamWriter.close();

    return 0;
}

void Split(std::string &str, char separator, std::vector<std::string> *resultSubstrings)
{
    std::istringstream splitStream(str);
    std::string newSubstring;
    while (std::getline(splitStream, newSubstring, separator))
        resultSubstrings->push_back(newSubstring);
}
std::string Join(std::vector<std::string> substrings, char separator)
{
    std::string str;
    std::ostringstream joinStream;
    for (uint32_t i = 0; i < substrings.size(); i++)
        if (i < substrings.size() - 1)
            joinStream << substrings[i] << separator;
        else
            joinStream << substrings[i];
    return joinStream.str();
}
