#ifndef TEXTGENERATOR_H
#define TEXTGENERATOR_H

#include <cstdint>
#include <string>
#include <map>
#include <queue>

typedef std::queue<std::string> prefix_t;
typedef std::map<prefix_t, std::vector<std::string>> prefix_table_t;

struct text_seed_t
{
    prefix_t firstPrefix;
    prefix_table_t prefixTable;
};

class TextGenerator
{
private:
    static constexpr int32_t c_prefixSize = 2;
    static constexpr int32_t c_textSize = 1000;

public:
    static text_seed_t CreateTextSeed(std::vector<std::string> words);
    static std::vector<std::string> GenerateText(text_seed_t textSeed);
};

#endif // TEXTGENERATOR_H
