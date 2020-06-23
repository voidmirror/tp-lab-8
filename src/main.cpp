#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <ctime>
#include <string>

using namespace std;

const int NPREF = 2;
const int MAXGEN = 1000;
int main()
{
	srand(time(NULL));
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	ifstream fin("input.txt");
	string word;
	prefix cur_prefix, temp_prefix;

	for (int i = 0; i < NPREF; i++)
	{
		fin >> word;
		cur_prefix.push_back(word);
	}

	temp_prefix = cur_prefix;
	while (fin >> word)
	{
		statetab[cur_prefix].push_back(word);
		cur_prefix.pop_front();
		cur_prefix.push_back(word);

	}
	cur_prefix = temp_prefix;


	ofstream fout("output.txt");
	while (!temp_prefix.empty())
	{
		fout << temp_prefix.front() << " ";
		temp_prefix.pop_front();
	}
	for (int i = NPREF; i < MAXGEN; i++)
	{
		if (statetab[cur_prefix].empty())
			break;
		int ind = rand() % statetab[cur_prefix].size();
		fout << statetab[cur_prefix][ind] << " ";
		if (i % 10 == 0)
			fout << endl;

		cur_prefix.push_back(statetab[cur_prefix][ind]);
		cur_prefix.pop_front();

	}
	fout.close();

	return 0;
}
