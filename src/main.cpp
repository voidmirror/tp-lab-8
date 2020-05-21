#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <time.h>

const int NPREF = 2;
const int MAXGEN = 1000;
typedef std::queue<std::string> prefix;

int main() {
	srand(time(nullptr));
	std::map<prefix, std::vector<std::string> > statetab;
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

	prefix current_prefix, first_prefix;
	std::string word;
	for (int i = 0; i < NPREF; i++) {
		in >> word;
		current_prefix.push(word);
	}

	first_prefix = current_prefix;
	while (in >> word) {
		statetab[current_prefix].push_back(word);
		current_prefix.pop();
		current_prefix.push(word);
	}
	current_prefix = first_prefix;

	while (!first_prefix.empty()) {
		out << first_prefix.front() << " ";
		first_prefix.pop();
	}

	for (int i = 0; i < MAXGEN; i++) {
		if (statetab[current_prefix].empty())
			break;
		int num = rand()%statetab[current_prefix].size();
		std::string postfix = statetab[current_prefix][num];
		out << postfix << " ";
		current_prefix.pop();
		current_prefix.push(postfix);
	}

	return 0;
}