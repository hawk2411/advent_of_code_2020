#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <sstream>
#include <algorithm>

struct password_definition_t {
    unsigned int min;
    unsigned int max;
    char c;
    std::string password;

    [[nodiscard]] bool isValid()const{
        if( (password[min-1] == c)  && (password[max-1] == c ) )
            return false;
        if( (password[min-1] == c)  || (password[max-1] == c ) )
            return true;

        return false;
    }

    static void parseMinMax(const std::string &min_max, password_definition_t *password) {
        auto pos =  min_max.find('-');
        password->min = std::stoi(min_max.substr(0, pos));
        password->max = std::stoi(min_max.substr(pos+1, min_max.size()));
    }

    static password_definition_t *createPasswordDefinition(const std::string &line) {
        auto* password = new password_definition_t;
        std::stringstream input_stream(line);

        std::string sub_line;
        if(! std::getline(input_stream, sub_line, ' ' )){
            throw std::exception();
        }
        parseMinMax(sub_line, password);

        if(!std::getline(input_stream, sub_line, ' ')) {
            throw std::exception();
        }
        password->c = sub_line[0];

        if(!std::getline(input_stream, sub_line, ' ')) {
            throw std::exception();
        }
        password->password = sub_line;

        return password;
    }

};


password_definition_t *createPasswordDefinition(const std::string &basicString);

int main() {
    std::ifstream passwords("./input_data.txt");
    if(!passwords.is_open()) return 1;

    std::string line;
    unsigned int result = 0;
    while(std::getline(passwords, line)) {
        std::unique_ptr<password_definition_t> password = std::unique_ptr<password_definition_t>(password_definition_t::createPasswordDefinition(line));

        if(password->isValid()){
            result++;
        }
    }
    passwords.close();
    std::cout << "The count of valid passwords is: " << result;
   
    return 0;
}

