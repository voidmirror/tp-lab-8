#include "TextGenerator.h"

int main()
{
    //TextGenerator generator;
    //std::string str = "это знаковая система произвольной природы, посредством которой осуществляется человеческое общение на различных уровнях коммуникации и трансляции, включая операции мышления, приобретение, хранение, преобразование и передачу сообщений (сигналов, информации, знаний) и связанные процессы. ";
    //std::string str = "На третьей итерации  совпал только первый символ искомой строки, а вот второй уже не совпадает. Придется первому циклу продолжить работу. Четвертая итерация дает необходимые  результаты – совпадают все символы искомой строки с частью исходной строки. А раз все символы совпали – подстрока найдена. Работу алгоритма можно закончить.";
    //generator.analysis("A AA. B BB");
    //generator.analysis(str);
    //generator.printTable();
    //std::string res = generator.generateStr();
    //std::cout << "res:"<< res << std::endl;
    //generator.printTable();
    
    TextGenerator generator;
    //std::string res = generator.readFileAndGenerateText("text.txt");
    std::string res = generator.readFileAndGenerateText("shinel.txt");
    std::cout << res << std::endl;
    
    return 0;
}