//
// Created by hawk on 15.07.21.
//
#include <string>
#include <algorithm>

#include "StringTools.h"

void StringTools::ltrim_digit_and_space(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isdigit(ch) && !std::isspace(ch);
    }));
}

void StringTools::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void StringTools::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void StringTools::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
