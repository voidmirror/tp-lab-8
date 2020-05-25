
#include <iostream>
#include <time.h>
#include <deque>
#include <map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int NPREF = 2;
const int MAXGEN = 1000;	

typedef deque<string> prefix;

int main()
{
	srand(time(NULL));
	map<prefix, vector<string>> statetab;
	ifstream file("input.txt");
	setlocale(LC_ALL, "Rus");
	ofstream result("output.txt");
	prefix pref, current_pref;
	string word;
	for (int i = 0; i < NPREF; i++)
	{
		file >> word;
		current_pref.push_back(word);
	}
	pref = current_pref;
	while (file >> word)
	{
		statetab[current_pref].push_back(word);
		current_pref.pop_front();
		current_pref.push_back(word);
	}
	current_pref = pref;
	for (string word : pref)
		result << word << " ";
	for (int i = NPREF; i < MAXGEN; i++)
	{
		if (statetab[current_pref].empty())
		{
			break;
		}
		else
		{
			int num = rand() % statetab[current_pref].size();
			result << statetab[current_pref][num] << " ";
			if (i % 10 == 0 && i != 0)
			{
				result << endl;
			}
			current_pref.push_back(statetab[current_pref][num]);
			current_pref.pop_front();
		}
	}
	file.close();
	result.close();
	return 0;
}