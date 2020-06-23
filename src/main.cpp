#include <iostream>
#include <ctime>
#include <deque>
#include <map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int NPREF = 2;					// количество слов в префиксе
const int MAXGEN = 1000;				// объем текста на выходе

typedef deque<string> prefix;			// очередь префиксов 

int main() 
{
	srand((unsigned int)time(nullptr));

	ifstream input_file("input.txt");
	if (!input_file)
	{
		cout << "Error ~ Unable to open input file ... \n";
		return -1;
	}
	ofstream output_file("output.txt");

	map< prefix, vector<string> > statetab; // префикс-суффиксы
	prefix first_prefix, current_prefix;
	string word;

	for (int i = 0; i < NPREF; i++) 
	{
		input_file >> word;
		current_prefix.push_back(word);
	}
	first_prefix = current_prefix;
	while (input_file >> word) 
	{
		statetab[current_prefix].push_back(word);
		current_prefix.pop_front();
		current_prefix.push_back(word);
	}
	current_prefix = first_prefix;
	while (!first_prefix.empty()) 
	{
		output_file << first_prefix.front() << " ";
		first_prefix.pop_front();
	}
	for (int i = NPREF; i < MAXGEN; i++) 
	{
		if (statetab[current_prefix].empty())
		{
			break;
		}
		else
		{
			int suffix_num = rand() % statetab[current_prefix].size();
			output_file << statetab[current_prefix][suffix_num] << " ";
			if (i % 10 == 0 && i != 0)
			{
				output_file << endl;
			}
			current_prefix.push_back(statetab[current_prefix][suffix_num]);
			current_prefix.pop_front();
		}
	}
	return 0;
}
