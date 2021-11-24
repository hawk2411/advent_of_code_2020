#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <vector>
#include <numeric>

auto getWeakNumber(const std::vector<unsigned int>& data) {
    const unsigned int preamble = 25;

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
            return current;
        }
    }
    return data.end();
}

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    std::vector<unsigned int > data;

    while(std::getline(input_data, line)) {
        data.push_back(std::strtol(line.c_str(), nullptr, 10));
    }

    auto weak_number = getWeakNumber(data);
    if(weak_number == data.end() ){
        std::cerr << "Cannot found a weak number: " << std::endl;
        return 1;
    }


    for(auto current = data.cbegin(); current != weak_number; current++) {
        unsigned int sum = *current;

        for(auto next_it = std::next(current); next_it != weak_number; next_it++ ) {

            sum += *next_it;
            if( sum == *weak_number) {
                std::vector<unsigned int> result_sequence;
                std::copy(current, next_it, std::back_inserter(result_sequence));

                std::sort(result_sequence.begin(), result_sequence.end());
                std::cout << "Result is: " << *result_sequence.begin() + *std::prev(result_sequence.end()) << std::endl;
                return 0;
            }
            else {
                if( sum > *weak_number ) break;
            }

        }
    }
    std::cout << "Error. " << std::endl;

    return 1;
}
