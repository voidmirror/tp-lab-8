#pragma once
#include "generator.h"

int main() {
	setlocale(LC_ALL, "Russian");

	/*Generator gen;

	gen.makeTable("input.txt");
	gen.generateText("output.txt");
	gen.printTableTo("table.txt"); */

	// or

	Generator gen("table.txt");

	gen.generateText("output.txt");
	gen.printTableTo();

	return 0;
}