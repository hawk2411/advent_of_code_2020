#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

static inline void ltrim_digit_and_space(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isdigit(ch) && !std::isspace(ch);
    }));
}

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


struct sub_bag_t {
    std::size_t count = 0;
    std::string bag_name;

    bool operator<(const sub_bag_t &bag) const {
        return bag_name < bag.bag_name;
    }
};

struct bag_t;
typedef std::map<std::string, std::unique_ptr<bag_t>> bag_rules_t;

struct bag_t {
    std::string name;
    std::set<std::unique_ptr<sub_bag_t>> sub_bags;

    bool operator<(const bag_t &bag) const {
        return name < bag.name;
    }


    std::size_t countSubBags(const bag_rules_t &bags) const {
        std::size_t sum = 0;

        for (const auto &sub_bag : sub_bags) {
            const auto &it = bags.find(sub_bag->bag_name);
            sum += sub_bag->count;
            if (it != bags.end()) {
                sum += sub_bag->count * it->second->countSubBags(bags);
            }
        }
        return sum;
    }
};

typedef std::map<std::string, std::unique_ptr<bag_t>> bag_rules_t;

std::size_t getCountChildren(const std::string &line);

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    const std::string bag_sub_bag_separator = " bags contain ";
    const std::string no_sub_bag_mark = "no other bags.";
    const std::string name_to_search = "shiny gold";
    bag_t *bag_to_search = nullptr;

    bag_rules_t bag_rules;

    while (std::getline(input_data, line)) {
        auto contain_pos = line.find(bag_sub_bag_separator);
        if (contain_pos == std::string::npos) {
            std::cerr << "Syntax error: Didn't find key word 'contain'";
            return 1;
        }
        auto bag = std::make_unique<bag_t>();
        std::string parent = line.substr(0, contain_pos);
        std::string kids_raw = line.substr(contain_pos + bag_sub_bag_separator.size());
        bag->name = parent;
        if (bag->name == name_to_search) {
            bag_to_search = bag.get();
        }
        if (kids_raw.find(no_sub_bag_mark) == std::string::npos) {
            std::stringstream ss(kids_raw);
            std::string name;

            while (std::getline(ss, name, ',')) {
                auto sub_bag = std::make_unique<sub_bag_t>();
                trim(name);
                std::size_t count_children = getCountChildren(name);
                ltrim_digit_and_space(name);
                name = name.substr(0, name.find_last_of(' '));

                sub_bag->bag_name = name;
                sub_bag->count = count_children;
                std::cout << "Bo: -" << name << "-\n";
                bag->sub_bags.insert(std::move(sub_bag));
            }
        }
        bag_rules.insert(std::make_pair(bag->name, std::move(bag)));

    }

    std::size_t count = bag_to_search->countSubBags(bag_rules);

    std::cout << "Result " << count << std::endl;
    return 0;
}


std::size_t getCountChildren(const std::string &line) {
    return std::stoi(line);
}
