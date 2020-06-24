#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <vector>
#include <string>

using namespace std;

typedef deque<string> prefix;          // очередь префиксов
const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе

map<prefix, vector<string>> readFile(string filename) {
    map<prefix, vector<string>> statetab;   // префикс-суффиксы
    prefix initial_prefix;
    string word;

    ifstream input_file(filename);

    if (!input_file.is_open()) {
        cout << "File is not open" << endl;
    } else {
        for (int i = 0; i < NPREF; i++) {
            input_file >> word;
            initial_prefix.push_back(word);
        }
        while (input_file >> word) {
            statetab[initial_prefix].push_back(word);
            initial_prefix.pop_front();
            initial_prefix.push_back(word);
        }
        input_file.close();
    }
    return statetab;
}

void createText(map<prefix, vector<string>> statetab, string input_name, string output_name) {
    ifstream input_file(input_name);
    string word;
    prefix initial_prefix;
    int ind;
    if (input_file) {
        for (int i = 0; i < NPREF; i++) {
            input_file >> word;
            initial_prefix.push_back(word);
        }
        input_file.close();

        ofstream output_file(output_name);
        for (auto word : initial_prefix) {
            output_file << word << " ";
        }
        for (int i = NPREF; i < MAXGEN; i++) {
            if (statetab.count(initial_prefix) != 0) {
                ind = rand() % statetab[initial_prefix].size();
                output_file << statetab[initial_prefix][ind]<<" ";
                initial_prefix.push_back(statetab[initial_prefix][ind]);
                initial_prefix.pop_front();
            }
        }
        output_file.close();
    }
}

int main() {
    string input_file = "../input.txt";
    string output_file = "../output.txt";
    map<prefix, vector<string>> statetab = readFile(input_file);
    createText(statetab, input_file, output_file);
}
