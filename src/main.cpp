//
// Created by Mikhail on 21.05.2020.
//

#include <task1.h>
#include <iostream>

int main() {

    if(fillStateTab("../res/input.txt") && outData("../res/output.txt")) {
        std::cout << "Данные успешно обработаны и выведены";
    }

}