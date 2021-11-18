//
// Created by hawk on 15.07.21.
//

#ifndef DAY8_STRINGTOOLS_H
#define DAY8_STRINGTOOLS_H


class StringTools {
public:
    static inline void ltrim_digit_and_space(std::string &s);

// trim from start (in place)
    static inline void ltrim(std::string &s);

// trim from end (in place)
    static inline void rtrim(std::string &s);

// trim from both ends (in place)
    static inline void trim(std::string &s);

};


#endif //DAY8_STRINGTOOLS_H
