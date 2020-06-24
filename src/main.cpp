#include <iostream>
#include <deque>
#include <queue>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	const int NPREF = 2;
	const int MAXGEN = 100;
	const int STRLEN = 10;

	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	prefix pref, init_pref;

	ifstream fin("input.txt");
	ofstream fout("output.txt");
	

	string word;
	for (size_t i = 0; i < NPREF; i++)
	{
		fin >> word;
		pref.push_back(word);
	}
	
	init_pref = pref;
	
	while (fin >> word)
	{
		statetab[pref].push_back(word);
		pref.pop_front();
		pref.push_back(word);
	}
	
	pref = init_pref;

	for (size_t i = 0; i < NPREF; i++)
	{
		fout << init_pref[i] << ' ';
	}

	for (size_t i = NPREF; i < MAXGEN; i++)
	{
		if (statetab[pref].empty())
			break;
		size_t suffix_key = rand() % statetab[pref].size();
		if ((i % STRLEN) == 0)
			fout << endl;
		fout << statetab[pref][suffix_key] << ' ';
		pref.push_back(statetab[pref][suffix_key]);
		pref.pop_front();
	}
	
	fin.close();
	fout.close();
	getchar();
	return 0;
}