#include <fstream>
#include "funcs.h"

using namespace std;

int main() {
    ifstream input("../data/input_text.txt");
    ofstream output("../data/output_text.txt");
    map<Prefix, vector<string>> statetab;

    Prefix startPrefix;
    if (input.is_open()) {
        makeTable(input, startPrefix, statetab);
        input.close();
    }
    if (output.is_open()) {
        generateText(output, startPrefix, statetab);
        output.close();
    }
}
