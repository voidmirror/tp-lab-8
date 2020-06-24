#include <fstream>
#include <map>
#include <deque>
#include <vector>
#include <time.h>
#include <iostream>
#include <string>

typedef std::deque<std::string> prefix;  

const int NPREF = 2;  
const int MAXGEN = 1000;  

std::map<prefix, std::vector<std::string>> readFile(std::string filename)
{
	std::map<prefix, std::vector<std::string>> statetab; 
	std::string word;
	prefix current_prefix;
	std::vector<std::string> suffixes;

	std::ifstream file(filename);

	if (!file)
	{
		std::cout << "File was not found!" << std::endl;

		exit(0);
	}

	else
	{
		for (int i = 0; i < NPREF; i++)  
		{
			file >> word;
			current_prefix.push_back(word);
		}

		while (file >> word)  
		{
			if (statetab.count(current_prefix) != 0)
			{
				statetab[current_prefix].push_back(word);
			}

			else
			{
				suffixes.push_back(word);
				statetab.insert(make_pair(current_prefix, suffixes));
				suffixes.clear();
			}

			current_prefix.pop_front();
			current_prefix.push_back(word);
		}

		file.close();
	}


	return statetab;
}


void generateText(std::map<prefix, std::vector<std::string>> word_map, std::string filename)
{
	srand(time(0));
	int word_limit = 9;
	int rand_index;
	prefix current_prefix;

	std::ifstream file(filename);

	if (file)
	{

		for (int i = 0; i < NPREF; i++)  
		{
			std::string word;
			file >> word;
			current_prefix.push_back(word);
		}

		file.close();

		std::ofstream file;
		file.open("output.txt");

		for (auto& word : current_prefix)
		{
			file << word << " ";
		}

		for (int i = NPREF; i < MAXGEN; i++)
		{
			if (word_map.count(current_prefix) != 0)
			{
				rand_index = rand() % word_map[current_prefix].size();
				file << word_map[current_prefix][rand_index] << " ";
				current_prefix.push_back(word_map[current_prefix][rand_index]);
				current_prefix.pop_front();

				if (i > 0 and (i + 1) % word_limit == 0)
				{
					file << std::endl;
				}
			}
		}

		file.close();
	}

}


int main()
{
	setlocale(0, "");

	std::string file = "input.txt";

	std::map<prefix, std::vector<std::string>> word_table = readFile(file);
	generateText(word_table, file);
}