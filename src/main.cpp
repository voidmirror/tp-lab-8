#include <fstream>
#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#define PREFIX_SIZE 2
#define WORDS 1000

int main()
{
    setlocale(LC_ALL, "rus");
    std::srand(std::time(nullptr));

    std::ifstream fin("dataset.txt"); // открыли файл для чтения

    std::vector <std::string>words;
    for (char buff[50]; fin >> buff;)
    {
        words.push_back(buff);
    }
    
    std::map<std::deque<std::string>, std::vector<std::string>> statetab; // префикс-суффиксы

    for (size_t i = 0; i < words.size() - PREFIX_SIZE; i++)
    {
        std::deque<std::string> prefix;

        for (size_t j = i; j < i + PREFIX_SIZE; j++)
        {
            prefix.push_back(words[j]);
        }

        std::string value = words[i + PREFIX_SIZE];

        statetab[prefix].push_back(value);
    }

    #if 0 // для дебага
    {
        std::map<std::deque<std::string>, std::vector<std::string>> ::iterator it = statetab.begin();

        while (it != statetab.end())
        {
            std::deque<std::string> words = it->first;

            std::string key = "";
            for (size_t i = 0; i < words.size(); i++)
            {
                key = key + " " + words[i];
            }
            
            std::vector<std::string> waluesV = it->second;

            std::string values = "";
            for (size_t i = 0; i < waluesV.size(); i++)
            {
                values = values + ";" + waluesV[i];
            }

            std::cout << "key : " << key << "\n";
            std::cout << "walues : " << values << "\n";

            it++;
        }
    }
    #endif

    std::map<std::deque<std::string>, std::vector<std::string>> ::iterator it;

    it = statetab.begin();

    for (size_t i = 0; i < (std::rand() % words.size()) - PREFIX_SIZE; i++)
    {
        it++;
    }
    
    
    std::deque<std::string> prefix = it->first;
    std::string result = "";

    for (size_t i = 0; i < PREFIX_SIZE; i++)
    {
        result = result + prefix[i] + " ";
    }
    
    size_t i = PREFIX_SIZE;

    for (; (i < WORDS) && (statetab.count(prefix) > 0); i++)
    {
        std::vector<std::string> suffixes = statetab[prefix];
        std::string suffix = suffixes[std::rand() % suffixes.size()];

        for (size_t j = 0; j < PREFIX_SIZE - 1; j++)
        {
            prefix[j] = prefix[j + 1];
        }
        
        prefix[PREFIX_SIZE - 1] = suffix;
        result = result + suffix + " ";
    }
    
    if(i != WORDS)
    {
        result = result + "\nWARNING can't find suffix, stop at word " + std::to_string(i) + "\n";
    }

    std::ofstream fout;
    fout.open("output.txt");
    fout << result;
    fout.close();

    return 0;
}