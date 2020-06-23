#include <assert.h>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "TextGenerator.h"

text_seed_t TextGenerator::CreateTextSeed(std::vector<std::string> words)
{
    text_seed_t textSeed;
    prefix_table_t prefixTable;
    prefix_t prefix;

    assert(words.size() > c_prefixSize);
    for (int32_t i = 0; i < c_prefixSize; i++)
        prefix.push(words[i]);
    textSeed.firstPrefix = prefix;

    for (int32_t i = c_prefixSize; i < words.size(); i++)
    {
        std::string word = words[i];

        prefix_table_t::iterator iterator = prefixTable.find(prefix);
        if (iterator != prefixTable.end())
            iterator->second.push_back(word);
        else
            prefixTable[prefix] = std::vector<std::string>{ word };

        prefix.pop();
        prefix.push(word);
    }
    textSeed.prefixTable = prefixTable;

    return textSeed;
}

std::vector<std::string> TextGenerator::GenerateText(text_seed_t textSeed)
{
    std::vector<std::string> words;
    prefix_t prefix = textSeed.firstPrefix;
    while (prefix.size() > 0)
    {
        words.push_back(prefix.front());
        prefix.pop();
    }

    prefix = textSeed.firstPrefix;
    prefix_table_t prefixTable = textSeed.prefixTable;
    while (words.size() < c_textSize)
    {
        prefix_table_t::iterator iterator = prefixTable.find(prefix);
        if (iterator != prefixTable.end())
        {
            std::vector<std::string> wordsToPick = prefixTable[prefix];
            std::string word = wordsToPick[rand() % wordsToPick.size()];

            words.push_back(word);

            prefix.pop();
            prefix.push(word);
        }
        else
            break;
    }

    return words;
}
