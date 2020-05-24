#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>
#include <time.h>
using namespace std;

typedef deque<string> prefix; // очередь префиксов
const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; // объем текста на выходе 
const int out_str_len = 10;


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open()) {
		prefix starting_prefix, current_prefix;
		map<prefix, vector<string> > statetab; // префикс-суффиксы
		string current_word;

		for (int i = 0; i < NPREF; i++) {
			fin >> current_word;
			current_prefix.push_back(current_word); // помещаем первые NPREF слов 
		}
		starting_prefix = current_prefix;

		while (fin >> current_word) {
			statetab[current_prefix].push_back(current_word); // добавили к префиксу w1 и w2 суффикс
			current_prefix.pop_front(); 
			current_prefix.push_back(current_word); // замена w1 и w2 на w2 и w3
		}
		fin.close();

		ofstream fout;
		fout.open("output.txt");

		for (auto str : starting_prefix) {
			fout << str << " "; // печатаем первый префикс
		}
		current_prefix = starting_prefix; 		
		for (int i = NPREF; i < MAXGEN; i++) { // начинем с NPREF, так как за циклом уже вывели два слова 
			if (statetab[current_prefix].empty()) break; // если у префикса нет суффиксов, заканчиваем вывод
			int suffix_ind = rand() % statetab[current_prefix].size(); // рандомный индекс суффикса
			fout << statetab[current_prefix][suffix_ind] << " "; // печатаем рандомный суффикс
			if (i % out_str_len == 0) {
				fout << endl; 
			}
			current_prefix.push_back(statetab[current_prefix][suffix_ind]); 
			current_prefix.pop_front();
		}		

		fout.close();
		return 0;
	}
	else {
		cout << "Error opening a file" << endl;
		return -1;
	}
}