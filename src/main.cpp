#include <iostream>
#include <TextGenerator.h>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    TextGenerator* txtGen = new TextGenerator();
    txtGen->readFile("input.txt");
    txtGen->genTextIntoFile("output.txt");
    txtGen->readFile("input2.txt");
    txtGen->genTextIntoFile("output2.txt");

    return 0;
}
