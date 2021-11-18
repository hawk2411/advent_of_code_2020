#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <set>
#include <vector>
#include <memory>
#include <string>

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

size_t countYesAnswers(const std::vector< std::unique_ptr<std::set<char>>> &groupedAnswers) {
    if(groupedAnswers.empty()) return 0;
    if(groupedAnswers.size() == 1) return groupedAnswers[0]->size();

    std::size_t all_answered = 0;

    for(char c : *groupedAnswers[0]) {
        bool all = true;
        for( int i=1; i < groupedAnswers.size(); i++ ){
            if(groupedAnswers[i]->count(c) == 0) {
                all = false;
                break;
            }
        }
        if(all) {
            all_answered++;
        }
    }

    return all_answered;
}

int main() {

    std::ifstream stream("./input_data.txt");
    if(!stream.is_open()) return 1;

    std::vector<std::unique_ptr<std::set<char>>> groups;
    std::string line;
    std::size_t sum = 0;
    std::size_t person = -1;
    std::string group_line;
    while(std::getline(stream, line)) {
        if(line.empty()){
            sum += countYesAnswers(groups);
            groups.clear();
        }
        else {

            std::unique_ptr<std::set<char>> answer_person = std::make_unique<std::set<char>>();
            for(char q : line) {
                if(answer_person->count(q) == 0) {
                    answer_person->insert(q);
                }
            }
            groups.push_back(std::move(answer_person));
        }
    }
    if(!groups.empty()) {
        sum += countYesAnswers(groups);
    }
    std::cout << "Sum of questions: " << sum;
}


