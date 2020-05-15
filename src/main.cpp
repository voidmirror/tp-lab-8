#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    
    typedef deque<string> prefix;          // очередь префиксов
    map<prefix, vector<string> > statetab; // префикс-суффиксы

    const int NPREF = 2; // количество слов в префиксе
    const int MAXGEN = 1000; //объем текста на выходе

    ifstream file("../data/input.txt");
    string word;
    prefix pref, initial_pref;

    if (file.is_open()) {
        for (int i = 0; i < NPREF; i++) {
            file >> word;
            pref.push_back(word);
        }
        
        initial_pref = pref;
        
        while (file >> word) {
            statetab[pref].push_back(word);
            pref.pop_front();
            pref.push_back(word);
        }
    }

    pref = initial_pref;

    ofstream output("../data/output.txt");
    for (int i = 0; i < NPREF; i++)
        output << initial_pref[i] << ' ';
    
    for (int i = 0; i < MAXGEN; i++) {

        if (statetab[pref].empty())
            break;

        string postfix = statetab[pref][rand() % statetab[pref].size()];
        
        output << postfix << " ";
        if (i % 5 == 0)
            output << endl;

        pref.push_back(postfix);
        pref.pop_front();
    }

    file.close();
    output.close();
    
    return 0;
}