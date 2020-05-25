#include "Generator.h"

int main()
{
	Generator G;
	setlocale(LC_ALL, "RUS");
	ifstream input;
	input.open("Input.txt");
	if (!input.is_open()) {
		cout << "Ошибка при открытие файла(ввод)";
		return 0;
	}
	ofstream output("Output.txt");
	if (!output.is_open()) {
		cout << "Ошибка при открытие файла(вывод)";
		return 0;
	}
	G.inputData(input);
	G.generate(output);
	return 0;
}