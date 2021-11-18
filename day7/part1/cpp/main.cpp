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

typedef std::map<std::string, std::unique_ptr<std::set<std::string>>> bag_rules_t;
typedef std::set<std::string> set_bags_t;

set_bags_t *getParents(const bag_rules_t &bag_contains, const std::string &bag_search_for) {

    auto parent_key = std::find_if(bag_contains.begin(), bag_contains.end(),
                                   [bag_search_for](const auto &it) {
                                       return (it.second->count(bag_search_for) > 0);
                                   });
    auto *result = new set_bags_t();

    while (parent_key != bag_contains.end()) {
        std::cout << "Found parent: " << parent_key->first << "\n";
        if (result->count(parent_key->first) == 0) {
            result->insert(parent_key->first);
        }
        parent_key = std::find_if(++parent_key, bag_contains.end(),
                                  [bag_search_for](const auto &it) {
                                      return (it.second->count(bag_search_for) > 0);
                                  });
    }
    return result;
}

void countParents(const bag_rules_t &bag_contains, set_bags_t *kids, set_bags_t& result_list) {

    if (kids->empty()) return;

    for(const auto& kid: *kids) {
        auto new_kids = std::unique_ptr<set_bags_t>(getParents(bag_contains, kid));
        for(const auto& new_kid : *new_kids) {
            if(result_list.count(new_kid) == 0){
                result_list.insert(new_kid);
            }
        }
        countParents(bag_contains, new_kids.get(), result_list);
    }
}

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    const std::string parent_child_separator = " bags contain ";
    const std::string no_child_mark = "no other bags.";
    const std::string value_to_search = "shiny gold";

    std::map<std::string, std::unique_ptr<std::set<std::string>>> bag_contains;

    while (std::getline(input_data, line)) {
        auto contain_pos = line.find(parent_child_separator);
        if (contain_pos == std::string::npos) {
            std::cerr << "Syntax error: Didn't find key word 'contain'";
            return 1;
        }
        std::string parent = line.substr(0, contain_pos);
        std::string kids_raw = line.substr(contain_pos + parent_child_separator.size());
        auto children = std::make_unique<std::set<std::string>>();

        if (kids_raw.find(no_child_mark) != std::string::npos) {
            bag_contains.insert(std::make_pair(parent, std::move(children)));
        } else {
            std::stringstream ss(kids_raw);
            std::string child;

            while (std::getline(ss, child, ',')) {
                trim(child);
                ltrim_digit_and_space(child);
                child = child.substr(0, child.find_last_of(' '));
                std::cout << "Bo: -" << child << "-\n";
                children->insert(child);
            }
            bag_contains.insert(std::make_pair(parent, std::move(children)));
        }
    }

    auto start_with = std::make_unique<set_bags_t>();
    set_bags_t result;
    start_with->insert(value_to_search);

    countParents(bag_contains, start_with.get(), result);

    auto count_parents = result.size();
    std::cout << "Result " << count_parents << std::endl;
    return 0;
}
