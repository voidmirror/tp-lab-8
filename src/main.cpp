#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <algorithm>
#include <time.h>
#include <clocale>

using namespace std;

typedef deque<string> prefix;

const int NPREF = 2;
const int MAXGEN = 150;

int main(){
	setlocale(LC_ALL, "rus");
	srand(time(0));
	ifstream inp1("skazka.txt");
	string w;
	prefix que;
	prefix pr_base;
	map<prefix, vector<string>> statetab;
	int rand_trigger;
	int j = 0;

	ofstream outp("skazka_edited.txt", ios_base::out, ios_base::trunc);
	ifstream del("deleted.txt");
	string buf;
	string del_buf;
	string rep_buf;
	getline(del, del_buf);
	getline(del, rep_buf);
	bool flag = false;
	while (getline(inp1, buf)){
		int size = buf.size();
		for (int i = 0; i < size; i++){
			flag = false;
			for (int k = 0; k < del_buf.size(); k++){
				if (buf[i] == del_buf[k]){
					buf.replace(i, 1, "");
					size = buf.size();
					flag = true;
					break;
				}
			}
			for (int l = 0; l < rep_buf.size(); l++){
				if (buf[i] == rep_buf[l]){
					buf.insert(i, " ");
					size = buf.size();
					i++;
					break;
				}
			}
			if (flag)
				i--;
		}
		outp << buf << endl;
	}
	outp.close();
	ifstream inp("skazka_edited.txt");


	for (int i = 0; i < NPREF; i++){
		inp >> w;
		que.push_back(w);
	}

	pr_base = que;
	
	while (inp >> w){
		/*
		if (pr_base == NAN){
			rand_trigger = rand() % 20;
			if (rand_trigger < 10)
				pr_base = que;
		}
		*/
		statetab[que].push_back(w);
		que.pop_front();
		que.push_back(w);
	}

	que = pr_base;
	
	for (int i = 0; i < MAXGEN; i++){
		j = rand() % (statetab[que].size());
		cout << statetab[que][j] << " ";
		pr_base = que;
		que.pop_front();
		que.push_back(statetab[pr_base][j]);
	}
	
	getchar();
	
	return 0;
}



