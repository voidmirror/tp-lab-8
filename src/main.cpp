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

	prefix pr, first_pr;
	std::string s;
	for (int i = 0; i < NPREF; i++) {
		in >> s;
		pr.push(s);
	}

	first_pr = pr;
	while (in >> s) {
		statetab[pr].push_back(s);
		pr.pop();
		pr.push(s);
	}
	pr = first_pr;

	while (!first_pr.empty()) {
		out << first_pr.front() << " ";
		first_pr.pop();
	}

	for (int i = 0; i < MAXGEN; i++) {
		if (statetab[pr].empty())
			break;
		int num = rand()%statetab[pr].size();
		std::string postfix = statetab[pr][num];
		out << postfix << " ";
		pr.pop();
		pr.push(postfix);
	}

	return 0;
}