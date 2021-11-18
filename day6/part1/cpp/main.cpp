#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <set>
#include <memory>
#include <string>


int main() {

    std::ifstream stream("./input_data.txt");
    if(!stream.is_open()) return 1;

    std::set<char> group_answers;
    std::string line;
    std::size_t sum = 0;
    while(std::getline(stream, line)) {
        if(line.empty()){
            group_answers.clear();
            continue;
        }
        for (char q: line) {
            if (group_answers.count(q) == 0) {
                group_answers.insert(q);
                sum++;
            }
        }
    }
    std::cout << "Sum of questions: " << sum;
}


