#include<map>
//#include<queue>
#include<deque>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
using namespace std;

typedef deque<string> prefix; // очередь префиксов

const int NPREF = 2; // количество слов в префиксе
const int MAXGEN = 1000; //объем текста на выходе

int main() {
	srand(time(NULL));

	ofstream outputF;
	ifstream inputF;

	inputF.open("input.txt");
	if (!inputF.is_open())
	{
		cout << "input OPENING ERR" << endl;
		return 1;
	}
	prefix first;
	string buff = "";
	for (int i = 0; i < NPREF; i++)
	{
		inputF >> buff;
		first.push_back(buff);
	}
	map<prefix, vector<string> > statetab; // префикс-суффиксы
	prefix cur = first;
	while (!inputF.eof()) {
		
		inputF >> buff;
		statetab[cur].push_back(buff);
		cur.pop_front();
		cur.push_back(buff);
	}
	inputF.close();
	outputF.open("output.txt");
	if (!outputF.is_open())
	{
		cout << "output OPENING ERR";
		return 2;
	}
	cur = first;
	vector<string>* suff_ptr = nullptr;
	suff_ptr = & statetab[first];
	for (string str : first)
	{
		outputF << str << " ";
	}
	int curSize = NPREF;
	while ( (!suff_ptr->empty()) && curSize < MAXGEN)
	{
		buff = suff_ptr->at(rand() % suff_ptr->size());
		outputF << buff << " ";
		cur.pop_front();
		cur.push_back(buff);
		curSize++;
		suff_ptr = &statetab[cur];
	}
	outputF.close();
	return 0;
}