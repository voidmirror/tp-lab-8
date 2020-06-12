#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>

const int NPREF = 2;
const int MaXGEN = 1000;
typedef std::deque<std::string> prefix;
typedef unsigned int uint;

void generator() {
	setlocale(LC_ALL, "Russian");

	std::map < prefix, std::vector < std::string>> statetab;
	std::string str;
	prefix pref;
	prefix begin;
	std::ifstream streamin("input.txt");
	if (!streamin.is_open())
	{
		std::cout << "ERROR" << std::endl;
	}
	else {
		for (uint i = 0; i < NPREF; i++) {
			streamin >> str;
			pref.push_back(str);
		}

		begin = pref;

		while (streamin >> str) {

			statetab[pref].push_back(str);

			pref.pop_front();
			pref.push_back(str);
		}

		streamin.close();
		std::ofstream streamout("output.txt");
		int numPostf;
		for (uint i = 0; i < NPREF; i++) {
			streamout << begin[i] << " ";
		}
		srand(time(NULL));
		pref = begin;
		srand(time(NULL));
		int index;
		for (int i = 0; i < MaXGEN - 2; i++)
		{
			if (statetab.find(pref) == statetab.end())
			{
				break;
			}
			else

			{
				index = rand() % statetab[pref].size();
				streamout << statetab[pref][index] << " ";
				if (i % 5 == 0) streamout << std::endl;
				pref.push_back(statetab[pref][index]);
				pref.pop_front();
			}
		}
		streamout.close();
	}
	
}


int main()
{
	generator();
	return 0;
}