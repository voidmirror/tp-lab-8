#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

typedef deque<string> prefix;          // очередь префиксов
map<prefix, vector<string>> statetab; // префикс-суффиксы

const int NPREF = 5; // количество слов в префиксе
const int MAXGEN = 500; // объем текста на выходе

int main()
{
	srand(time(NULL)); // сброс генератора случайных чисел
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	prefix pref;
	pref.push_back("START_OF_STATEMENT");
	string input_word = "";
	while (cin >> input_word) // обработка входных данных
	{
		input_word[0] = tolower(input_word[0]); // приведение букв к нижнему регистру
		bool end_of_statement_flag = false;
		if (input_word[input_word.size() - 1] == '.' || input_word[input_word.size() - 1] == '!' || input_word[input_word.size() - 1] == '?')
		{ // проверка на обнаружение конца предложения
			end_of_statement_flag = true;
			input_word = input_word.substr(0, input_word.size() - 1);
		}
		statetab[pref].push_back(input_word); // обновление префикса
		pref.push_back(input_word);
		while (pref.size() > NPREF)
		{
			pref.pop_front();
		}
		if (end_of_statement_flag)
		{
			statetab[pref].push_back("END_OF_STATEMENT");
			pref.clear();
			pref.push_back("START_OF_STATEMENT");
		}
	}

	pref.clear();		// установка префикса начала предложения
	pref.push_back("START_OF_STATEMENT");
	for (int i = 0; i < MAXGEN; i++)
	{
		if (statetab.find(pref) == statetab.end()) // обработка случая ненахождения суффикса для текущего префикса
		{
			break;
		}

		string word_to_add = statetab[pref][rand() % statetab[pref].size()]; // выбор случайного слова из таблицы префикс-суффикс
		if (word_to_add == "END_OF_STATEMENT") // проверка окончания предложения
		{
			cout << '.'; // окончание предложения
			pref.clear();		// установка префикса начала предложения
			pref.push_back("START_OF_STATEMENT");
			i--; // новое слово не добавлено, итерация не засчитывается
			continue;
		}

		if (pref.size() == 1 && pref[0] == "START_OF_STATEMENT") // капитализация первой буквы в предложении
		{
			word_to_add[0] = toupper(word_to_add[0]);
		}
		
		cout << ' ' << word_to_add; // запись нового слова в предложении
		input_word[0] = tolower(input_word[0]); // приведение букв к нижнему регистру

		pref.push_back(word_to_add); // обновление префикса
		while (pref.size() > NPREF)
		{
			pref.pop_front();
		}
	}

	cout << ".\n"; // завершение генерации текста
}