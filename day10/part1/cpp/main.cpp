#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <vector>

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    std::vector<unsigned int > data;
    const unsigned int preamble = 25;

    while(std::getline(input_data, line)) {
        data.push_back(std::strtol(line.c_str(), nullptr, 10));
    }

    std::sort(data.begin(), data.end());
    unsigned int diff_1 {0},  diff_3 {0};
    unsigned int prev_number = 0;
    for (auto current : data) {
        unsigned int diff = current - prev_number;
        diff_1 += (diff == 1) ? 1 :0;
        diff_3 += (diff == 3) ? 1 :0;
        prev_number = current;
    }
    diff_3++;

    std::cout << "Solution is: " << diff_1 * diff_3 << std::endl;
    return 0;
}
