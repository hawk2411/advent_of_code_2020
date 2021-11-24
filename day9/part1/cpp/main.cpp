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

    for (auto current = data.begin() + preamble; current != data.end(); current++) {
        bool found = false;

        for (auto t = current - preamble; t != current; t++) {
            auto result = std::find_if(t, std::prev(current),
                                       [&current, &t](unsigned int digit){return ((*t + digit) == *current);});

            if(result != std::prev(current) || (*std::prev(current) + *t == *current)) {
                found = true;
                break;
            }
        }
        if(!found) {
            std::cout << "Result is: " << *current << std::endl;
            break;
        }
    }
    return 0;
}
