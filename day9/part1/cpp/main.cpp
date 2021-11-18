#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::cerr << "Found no solution" << std::endl;

}
