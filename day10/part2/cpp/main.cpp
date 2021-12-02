#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <set>

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    std::set<unsigned int> data;

    while(std::getline(input_data, line)) {
        data.insert(std::strtol(line.c_str(), nullptr, 10));
    }

    unsigned int variations = 0;
    unsigned int prev_number = 0;
    for (auto current : data) {
        for (int i: {1, 2, 3}) {
            auto res = prev_number + i;
            if ((data.count(res) > 0) ) {
                variations++;
            }
        }
        prev_number = current;
    }


    std::cout << "Solution is: " << variations << std::endl;
    return 0;
}
