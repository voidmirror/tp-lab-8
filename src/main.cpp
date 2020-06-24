#include<iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <cstdlib>
#include <random>
#include "task1.h"

using namespace std;
typedef deque<string> prefix;

int main() {
	vector<string> text = read_text("text1.txt");
	string result = generate_text(text);
	cout << result;
	ofstream outp("result.txt");
	outp << result;
	outp.close();
	return 0;
}

