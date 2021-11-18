#include <iostream>
#include <fstream>
#include <set>
#include <string>

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream expense_report(input_file);
    if(!expense_report.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string line;
    std::set<int> ordered_numbers;
    while (std::getline(expense_report, line)) {
        ordered_numbers.insert(std::stoi(line));
    }
    expense_report.close();

    for(auto number: ordered_numbers) {
        if(ordered_numbers.find(2020 - number) != ordered_numbers.end()) {
            std::cout << "The number is: " << (2020 - number) * number;
            break;
        }
    }

    return 0;
}
