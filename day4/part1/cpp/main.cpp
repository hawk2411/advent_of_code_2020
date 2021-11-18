#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <string>

bool isPassportValid(const std::string &basicString);

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

    std::string line;
    std::string passport;
    unsigned int validPassports = 0;
    while(std::getline(stream, line)){
        trim(line);
        if(!line.empty() ) {
            if(! passport.empty()) {
                passport += " ";
            }
            passport +=  line;
        }
        else{
            if( isPassportValid(passport+" ") ) {
                validPassports++;
            }
            passport="";
        }

    }
    if(!passport.empty()) {
        if( isPassportValid(passport+" ") ) {
            validPassports++;
        }
        passport="";
    }

    std::cout << "Count of valid passports: " << validPassports << std::endl;
    return 0;
}

bool isPassportValid(const std::string &passport) {

    const int count_keys = 8;
    std::array<std::string, count_keys> keys = {
            "byr:",
            "iyr:",
            "eyr:",
            "hgt:",
            "hcl:",
            "ecl:",
            "pid",
            "cid:"
    };
    int found_keys = 0;
    bool cid_is_missing = true;
    for(const auto& key : keys) {
        auto find_result = passport.find(key);
        if(find_result == std::string::npos){
            if(key != keys[7]){
                return false;
            }
        }
        else{
            std::string value = passport.substr(find_result, passport.find(" ", find_result));
        }

    }
    return true;
}
