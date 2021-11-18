#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <functional>
#include <valarray>
#include <string>

unsigned int getRow(const std::string &code);

unsigned int getCol(const std::string &code);

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

int main() {

    std::ifstream stream("./input_data.txt");
    if(!stream.is_open()) return 1;

    unsigned int highest_seat_id = 0;
    std::string line;
    while(std::getline(stream, line)) {
        unsigned int row = getRow(line.substr(0, 7));
        unsigned int col = getCol(line.substr(7, 3));
        unsigned int current_seat_id = row * 8 + col;
        if(current_seat_id > highest_seat_id) {
            highest_seat_id = current_seat_id;
        }
    }
    std::cout << "Highest seat id: " << highest_seat_id << std::endl;
    return 0;
}

unsigned int getCol(const std::string &code) {
    const unsigned int count_cols = 8;
    unsigned int current_no, col = count_cols;

    for(int i=0; i < 3; i++) {
        const char row_operator =code[i];
        current_no = count_cols / pow(2, i + 1);
        if(row_operator == 'L') {
            col = col - current_no;
        }
    }
    return col - 1;
}

unsigned int getRow(const std::string &code) {

    const unsigned int count_rows = 128;
    unsigned int current_no, row = count_rows;

    for(int i=0; i < 7; i++) {
        const char row_operator =code[i];
        current_no = count_rows / pow(2, i + 1);
        if(row_operator == 'F') {
            row = row - current_no;
        }
    }
    return row - 1;
}
