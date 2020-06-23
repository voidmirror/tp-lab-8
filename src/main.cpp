#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include<string>

using namespace std;

const size_t n_word_in_prefix = 1;
const size_t size_output_text = 100;

int main() {
    typedef deque<string> prefix;
    map<prefix, vector<string>> statetab;

    const string input_path = R"(../data/input.txt)";
    const string output_path = R"(../data/output.txt)";

    prefix pref;
    prefix initialWords;

    //создаем таблицу префиксы : суффикс
    ifstream input_stream(input_path);
    if (input_stream.is_open())
    {
        string str;
        for (size_t i = 0; i < n_word_in_prefix; i++) {
            input_stream >> str;
            pref.push_back(str);
        }

        initialWords = pref;

        while (input_stream >> str) {
            statetab[pref].push_back(str);
            pref.pop_front();
            pref.push_back(str);
        }
    }
    else {
        cout << "cannot open input.txt" << endl;
        return 1;
    }
    input_stream.close();

    ofstream output_stream(output_path);

    for (size_t i = 0; i < n_word_in_prefix; i++) {
        output_stream << initialWords[i] << " ";
    }

    map<prefix, vector<string>>::iterator it;
    pref = initialWords;

    string suff;
    for (size_t i = 0; i < size_output_text; i++)
    {
        // ищем набор суффиксов по префиксу
        it = statetab.find(pref);
        if (it!=statetab.end())
        {
            //выбираем рандомный суффикс
            suff = it->second[random() % (it->second).size()];
            //записываем в выходной файл
            output_stream << suff << " ";
            //генерируем новый префикс
            pref.pop_front();
            pref.push_back(suff);
        }
    }
    return 0;
}