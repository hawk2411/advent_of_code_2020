#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include "CodeLine.h"
#include "Computer.h"

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    Computer computer;
    while (std::getline(input_data, line)) {
        auto* codeLine =  CodeLine::generateCodeLine(line);
        if(codeLine == nullptr) {
            break;
        }
        computer.insertCodeLine(codeLine);
    }
    if( computer.manipulateProgram() ) {
        std::cout << "Result "<< computer.getAccumulator() <<  std::endl;
        return 0;
    }
    std::cerr << "Found no solution" << std::endl;

}
