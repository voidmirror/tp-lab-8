#include "main.h"

int main()
{
	map<prefix, vector<string> > statetab;

	setlocale(LC_ALL, "rus");
	ifstream inputFile("input.txt");

	if (!inputFile.is_open())
	{
		cout << "Input file is not open!" << endl;
		return -1;
	}

	prefix first, second;
	string word;

	for (size_t i = 0; i < NPREF; i++)
	{
		inputFile >> word;
		first.push_back(word);
	}


	second = first;

	while (inputFile >> word)
	{
		statetab[second].push_back(word);
		second.pop_front();
		second.push_back(word);
	}
	inputFile.close();

	srand(time(0));
	ofstream outputFile("output.txt");

	if (!outputFile.is_open())
	{
		cout << "Output file is not open!" << endl;
		return -1;
	}

	for (auto word: first)
	{
		outputFile << word << " ";
	}

	for (size_t i = NPREF; i < MAXGEN; i++)
	{
		if (statetab[first].empty()) continue;

		if (!(i % 5)) outputFile << endl;

		size_t index = rand() % statetab[first].size();
		string suffix = statetab[first][index];
		outputFile << suffix << " ";
		first.pop_front();
		first.push_back(suffix);
	}
	outputFile.close();
}