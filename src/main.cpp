#include <iostream>
#include <fstream>
#include <deque>
#include <map>
#include <vector>
#include <time.h>

using namespace std;

const int NPREF = 2; // number of words in the prefix
const int MAXGEN = 1000; // output text volume
const int LENLINE = 5; 
typedef deque<string> prefix;


int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	srand(time(0));

	map<prefix, vector<string>> statetab;

	prefix pref, init_pref;
	string str;

	for (int i = 0; i < NPREF; i++)
	{
		input >> str;
		pref.push_back(str);
	}

	init_pref = pref;

	while (input >> str)
	{
		statetab[pref].push_back(str);
		pref.pop_front();
		pref.push_back(str);
	}

	pref = init_pref;

	for (string str : init_pref)
		output << str << " ";

	for (int i = NPREF; i < MAXGEN; i++)
	{
		if (!statetab[pref].empty())
		{
			int ind = rand() % statetab[pref].size();
			output << statetab[pref][ind] << " ";
			if (i % LENLINE == 0)
				output << endl;
			pref.push_back(statetab[pref][ind]);
			pref.pop_front();
		}
	}

	input.close();
	output.close();
	return 0;
}
