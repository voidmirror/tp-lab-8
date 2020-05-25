#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <deque>
#include <random>
using namespace std;

const int NPREF = 2;
const int MAXGEN = 2000;

typedef deque<string> prefix; // очередь префиксов

void readTable(const string& filename, map<prefix, vector<string>>& statetab, prefix& start)
{
    ifstream fin(filename);
    if (fin.is_open())
    {
        prefix first;
        string word;

        for (size_t i = 0; i < NPREF; i++)
        {
            fin >> word;
            first.push_back(word);
        }
        start = first;

        while (fin >> word)
        {
            statetab[first].push_back(word);
            first.pop_front();
            first.push_back(word);
        }

        fin.close();
    }
    else
    {
        cout << "file undefined" << endl;
        exit(EXIT_FAILURE);
    }
}

void genText(ostream& os, const map<prefix, vector<string>>& statetab, const prefix& start)
{
    auto prefs = start;
    for(const auto& pref : prefs)
    {
        os << pref << " ";
    }

    random_device rdev{};
    default_random_engine generator{rdev()};

    for (size_t i = NPREF; i < MAXGEN; i++)
    {
        auto it = statetab.find(prefs);
        if(it == statetab.cend())
        {
            break;
        }
        auto suffs = it->second;
        if(suffs.empty())
        {
            continue;
        }
        uniform_int_distribution<size_t> distribution_index(0, suffs.size() - 1);
        size_t index = distribution_index(generator);
        string suffix = suffs[index];

        os << suffix << " ";
        prefs.pop_front();
        prefs.push_back(suffix);

        if(i % 8 == 0)
        {
            os << endl;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    map<prefix, vector<string>> statetab; // префикс-суффиксы
    prefix start;
    readTable("input.txt", statetab, start);

    ofstream os("output.txt");
    if (os.is_open())
    {
        genText(os, statetab, start);
        os.close();
    }
    else
    {
        cout << "file undefined" << endl;
        exit(EXIT_FAILURE);
    }
}