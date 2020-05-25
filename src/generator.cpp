#include "generator.h"

void generator() {
	setlocale(LC_ALL, "Russian");

	std::map<prefix, std::vector<std::string>> statetab;
	std::map<prefix, std::vector<std::string>>::iterator it;
	std::string str;
	prefix pref;
	prefix start;
	std::ifstream stream1("input.txt");
	if (!stream1.is_open())
	{
		std::cout << "ERROR OPENING FILE" << std::endl;
	}
	else {
		for (uint i = 0; i < NPREF; i++) {
			stream1 >> str;
			pref.push_back(str);
		}

		start = pref;

		while (stream1 >> str) {

			statetab[pref].push_back(str);

			pref.pop_front();
			pref.push_back(str);
		}
	}
	std::ofstream stream2("output.txt");
	int numPostf;
	for (uint i = 0; i < NPREF; i++) {
		stream2 << start[i] << " ";
	}
	srand(time(NULL));
	pref = start;
	for (uint i = 0; i < MaXGEN; i++)
	{
		it = statetab.find(pref);
		if (it != statetab.end())
		{
			numPostf = rand() % (it->second).size();
			stream2 << it->second[numPostf] << " ";
			pref.pop_front();
			pref.push_back(it->second[numPostf]);
		}

	}
	stream2.close();
}