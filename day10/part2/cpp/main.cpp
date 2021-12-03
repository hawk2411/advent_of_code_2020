#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <set>
#include <vector>

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    std::set<unsigned int> data;
    std::vector<unsigned int> ordered_data;

    while(std::getline(input_data, line)) {
        int number = std::strtol(line.c_str(), nullptr, 10);
        data.insert(number);
        ordered_data.push_back(number);
    }

    std::sort(ordered_data.begin(), ordered_data.end());
    auto last_number = ordered_data.back();

    std::vector<unsigned int> must_have;
    unsigned int variations = 0;
    unsigned int prev_number = last_number+3;
    while(prev_number != 0) {
        for(auto diff : {3,2,1}) {
            auto must_have_number = prev_number - diff;
            if( data.contains(must_have_number) ) {
                must_have.push_back(must_have_number);
                prev_number = must_have_number;
                break;
            }
        }

    }


    std::cout << "Solution is: " <<  ordered_data.size() - must_have.size() << std::endl;
    return 0;
}
