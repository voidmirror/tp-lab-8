
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

typedef deque<string> prefix;
map <prefix, vector<string>> statetab;

const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе

int main()
{
	prefix Prefixes, TempPref;
	vector<string> Postfixes;

	setlocale(LC_ALL, "RUS");

	ifstream FileIn("InputText.txt");
	ofstream FileOut("Output.txt");

	//ifstream FileIn("Cvetaeva_Input.txt");
	//ofstream FileOut("Cvetaeva_Out.txt");
	
	
	if (FileIn.is_open())
	{
		string word;
		// input of first two words into prefixes
		for (int i = 0; i < NPREF; i++)
		{
			FileIn >> word;
			Prefixes.push_back(word);
		}

		TempPref = Prefixes;	// saving to use at the beginning of printing to the file
		// process of making prefixes and postfixes
		while (FileIn >> word)
		{
			statetab[Prefixes].push_back(word);
			Prefixes.pop_front();
			Prefixes.push_back(word);
		}

		FileIn.close();	// there is no use for that file anymore, because we already copied everything we need

		FileOut << TempPref[0] << " " << TempPref[1] << " ";	// first two word to the output file
		// making random postfixes and moving through prefixes
		for (int i = 0; i < MAXGEN; i++)
		{
			if (statetab[TempPref].empty()) break;
			int RandomIndex = rand() % statetab[TempPref].size();
			string Postfix = statetab[TempPref][RandomIndex];
			FileOut << Postfix << " ";
			if (i % 7 == 0) FileOut << endl;	// we dont want text to be one line, so lets separate it every 7 words with a new line

			// Deleting already used postfixes is written in the next two lines
			vector<string>::iterator position = find(statetab[TempPref].begin(), statetab[TempPref].end(), statetab[TempPref][RandomIndex]);
			if (position != statetab[TempPref].end()) statetab[TempPref].erase(position);

			TempPref.push_back(Postfix);
			TempPref.pop_front();
		}
		
		FileOut.close();


	}
	else cout << "File was not opened!" << endl;


	return 0;
}
