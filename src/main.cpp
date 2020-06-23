#include "TextGenerator.h"


int main()
{
    std::string inputFileName = "../input_text.txt";
    std::string outputFileName = "../output_text.txt";

    TextGenerator textGenerator = TextGenerator();
    textGenerator.generateText(inputFileName, outputFileName);
}
