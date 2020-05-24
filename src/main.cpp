// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <vector>
#include <time.h>
#include <string>
#include <iterator>

using namespace std;

typedef deque<string> prefix;

const int NPREF = 2;			
const int MAXGEN =1000;		


int main()
{
	setlocale(LC_ALL, "Russian");

	map<prefix, vector<string> > statetab;
	string word;
	prefix first_pref, second_pref;
	vector<string> suffix;
	//--------------------------------INTPUT----------------------------------//


	ifstream file("text.txt");
	

	if (!file)
	{
		cout << "bad";
	}
		
	else
	{
		cout << "good";
		for (int i = 0; i < NPREF; ++i)
		{
			file >> word;
			first_pref.push_back(word);
			second_pref.push_back(word);

		}

		while (file >> word)
		{
			if (statetab.find(first_pref) == statetab.end())
			{
				suffix.push_back(word);
				statetab.insert(make_pair(first_pref, suffix));
				suffix.clear();
			}else
			{
				statetab[first_pref].push_back(word);
			}
			first_pref.push_back(word);
			first_pref.pop_front();
		}
		file.close();
	}




	//--------------------------------OUTPUT----------------------------------//
	srand(time(0));
	int random_index;
	
	ofstream file2("result.txt");
	
	file2 << second_pref[0] << " " << second_pref[1] << " ";

	for (int i = 0; i < MAXGEN - 2; i++)
	{
		if (statetab.find(second_pref) == statetab.end())
		{
			cout << "end";
			break;
		} 
		else

		{
			random_index = rand() % statetab[second_pref].size();
			file2 << statetab[second_pref][random_index] << " ";
			if ((i + 1) % 8 == 0) 
				file2<< endl;
			second_pref.push_back(statetab[second_pref][random_index]);
			second_pref.pop_front();
		}
	}

	file2.close();

	//cout << "end";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
