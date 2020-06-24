#include "Generator.h"

void Generator::inputData(ifstream& input) {
	vector<string> sufix;
	prefix pref;
	string str;

	for (int i = 0; i < NPREF; i++) {
		input >> str;
		pref.push_back(str);
		initialPrefix.push_back(str);
	}

	while ((input >> str)) {
		if (statetab.count(pref) == 0) {
			sufix.push_back(str);
			statetab.insert(pair<prefix, vector<string> >(pref, sufix));
			sufix.clear();
		}
		else
			statetab[pref].push_back(str);
		pref.pop_front();
		pref.push_back(str);
	}
}

void Generator::generate(ofstream& output) {
	string str;
	prefix pref = initialPrefix;

	for (int i = 0; i < NPREF; i++)
		output << pref[i] << ' ';

	for (int i = 0; i < MAXGEN; i++) {
		srand(time(NULL));
		if (statetab.count(pref) != 0) {
			str = statetab[pref][rand() % (statetab[pref].size())];
			output << str << ' ';
			pref.pop_front();
			pref.push_back(str);
		}
		else {
			break;
		}
	}
}