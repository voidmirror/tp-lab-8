#include"task1.h"

vector<string> read_text(string filename) {
	string word;
	ifstream file("text1.txt");
	vector<string> text;
	if (file.is_open())
	{
		while (file >> word)
		{
			text.push_back(word);
		}
	}
	return text;
}

map<prefix, vector<string>> generate_prefix_table(vector<string> text) {
	map<prefix, vector<string> > statetab;
	prefix pref;

	for (size_t i = 0; i < NPREF; ++i) {
		pref.push_back(text[i]);
	}

	for (size_t i = NPREF; i < text.size(); ++i) {
		statetab[pref].push_back(text[i]);
		pref.erase(pref.begin());
		pref.push_back(text[i]);
	}
	return statetab;
}

string generate_text(vector<string> init_text) {
	prefix pref;
	string text;

	map<prefix, vector<string> > statetab = generate_prefix_table(init_text);
	for (size_t i = 0; i < NPREF; ++i) {
		pref.push_back(init_text[i]);
	}

	for (size_t i = 0; i < NPREF; ++i) {
		text.append(pref[i]);
		text.append(" ");
	}

	for (size_t i = 0; i < MAXGEN; ++i) {
		if (statetab[pref].empty())
		{
			break;
		}
		string word = random_word(statetab[pref]);
		text.append(word);
		text.append(" ");
		pref.erase(pref.begin());
		pref.push_back(word);
	}
	return text;
}

string random_word(vector<string> wordlist) {
	random_device rd;
	mt19937 mersenne(rd());
	int size = wordlist.size();
	return wordlist[mersenne() % size];
}