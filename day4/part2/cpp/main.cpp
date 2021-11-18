#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <functional>
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

bool byrValidation(const std::string& value){
    int byr = std::stoi(value);
    if(byr < 1920 || byr > 2002)
        return false;

    return true;
}
bool iyrValidation(const std::string& value){
    int iyr = std::stoi(value);
    if(iyr < 2010  || iyr > 2020)
        return false;
    return true;
}
bool eyrValidation(const std::string& value){
    int eyr = std::stoi(value);
    if(eyr < 2020  || eyr > 2030)
        return false;
    return true;
}
bool hgtValidation(const std::string& value){
    auto inch_pos = value.find("in");
    if(inch_pos != std::string::npos && (value.size() - inch_pos) == 2 ){
        std::string inch_str = value.substr(0, inch_pos);
        int inch = std::stoi(inch_str);
        if(inch >= 59 && inch <= 76) {
            return true;
        }
        else { return false; }
    }

    auto cm_pos = value.find("cm");
    if(cm_pos != std::string::npos && (value.size() - cm_pos) == 2 ){
        std::string cm_str = value.substr(0, cm_pos);
        int cm = std::stoi(cm_str);
        if(cm >= 150 && cm <= 193) {
            return true;
        }
    }

    return false;
}
bool hclValidation(const std::string& value){
    const std::string valid_chars = "0123456789abcdef";
    if(value.size() > 7) {
        return false;
    }
    if(value[0] != '#') {
        return false;
    }
    for(int i = 1; i < value.size(); i++ ){
        if( valid_chars.find(value[i]) == std::string::npos ) {
            return false;
        }
    }
    return true;
}
bool eclValidation(const std::string& value){
    std::array<std::string, 7> poss_colors {
            "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
    };
    for (const auto &color: poss_colors)
        if (color == value) {
            return true;
        };
    return false;
}
bool pidValidation(const std::string& value){
    if(value.size() != 9){
        return false;
    }

    for( const auto c: value) {
        if( !std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool cidValidation(const std::string& value){
    return true;
}


bool isPassportValid(const std::string &passport) {

    const int count_keys = 8;
    std::array<std::tuple<std::string, std::function<bool(const std::string&)>>, 8> keys = {
            std::make_tuple("byr:", byrValidation),
            std::make_tuple("iyr:", iyrValidation),
            std::make_tuple("eyr:", eyrValidation),
            std::make_tuple("hgt:", hgtValidation),
            std::make_tuple("hcl:", hclValidation),
            std::make_tuple("ecl:", eclValidation),
            std::make_tuple("pid:", pidValidation),
            std::make_tuple("cid:", cidValidation)
    };

    int found_keys = 0;
    bool cid_is_missing = true;
    for(const auto& item : keys) {
        auto find_result = passport.find(std::get<0>(item));
        if(find_result == std::string::npos){
            if(std::get<0>(item) != std::get<0>(keys[7])){
                return false;
            }
        }
        else{
            auto end_of_value = passport.find(' ', find_result+1);
            std::string value = passport.substr(find_result, end_of_value-find_result);
            value = value.substr(value.find(':')+1, value.size());
            if( !std::get<1>(item)(value)) {
                return false;
            }
        }

    }
    return true;
}
