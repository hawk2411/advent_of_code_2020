#include <iostream>
#include <fstream>
#include <set>
#include <string>

int main() {

    std::ifstream expense_report("./input_data.txt");
    if(!expense_report.is_open()) {
        return 1;
    }
    std::string line;
    std::set<int> ordered_numbers;
    while (std::getline(expense_report, line)) {
        ordered_numbers.insert(std::stoi(line));
    }
    expense_report.close();

    for(auto number: ordered_numbers) {
        for(auto second: ordered_numbers ) {
            if(number == second) continue;

            int third_number = 2020 - (number + second);
            if(ordered_numbers.find(third_number) != ordered_numbers.end()) {
                std::cout << "The number is: " <<  number * second * third_number;
                return 0;
            }
        }
    }

    return 0;
}
