#include "markovTextGen.h"

using namespace std;

int main() {
	const int NPREF = 2;
	const int MAXGEN = 1000;
	markovTextGen(NPREF, MAXGEN, "input.txt", "output.txt");
	
	return 0;
}