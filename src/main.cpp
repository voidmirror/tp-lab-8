//
//  main.cpp
//  TextGenerator
//
//  Created by Олеся Мартынюк on 18.05.2020.
//  Copyright © 2020 Olesia Martinyuk. All rights reserved.
//

#include <iostream>
#include "TextGenerator.h"

using namespace std;

int main(int argc, const char * argv[]) {
    TextGeterator generator;
    generator.generateText();
    generator.saveText();    
}
