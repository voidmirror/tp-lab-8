#include <iostream>
#include <deque>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include "stdafx.h"
#include <ctime>

using namespace std;

void main()
{
	typedef deque<string> prefix;          // очередь префиксов
	map<prefix, vector<string> > statetab; // префикс-суффиксы

	const int NPREF = 2; // количество слов в префиксе
	const int MAXGEN = 1000; //объем текста на выходе

	ofstream result("result.txt");

	setlocale(LC_ALL, "Rus");
	ifstream file("text.txt");
	string word;
	prefix pref1, pref;

	int i = 0;

	while (i < NPREF)
	{
		file >> word;
		pref1.push_back(word);
		result << word << " ";
		i++;
	}

	pref = pref1;

	while (file >> word)
	{
		statetab[pref].push_back(word);
		pref.pop_front();
		pref.push_back(word);
	}

	srand(time(NULL));

	for (i = NPREF; i < MAXGEN; i++)
	{

		if (statetab[pref1].empty())
		{
			break;
		}

		else
		{
			int suffnum = rand() % statetab[pref1].size();
			result << statetab[pref1][suffnum] << " ";
			pref1.push_back(statetab[pref1][suffnum]);
			pref1.pop_front();
		}
	}
}