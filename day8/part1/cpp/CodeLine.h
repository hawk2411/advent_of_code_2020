//
// Created by hawk on 15.07.21.
//

#ifndef DAY8_CODELINE_H
#define DAY8_CODELINE_H

#include <string>

enum class Command {
    NOP = 0,
    ACC = 1,
    JMP = 2
};

class CodeLine {
private:

    Command command_;
    int address_;
    bool executed_;

public:
    CodeLine(Command command, int address);

public:
    void setExecuted(bool executed);
    bool isExecuted() const;

    void setCommand(Command command);
    Command getCommand() const;

    int getAddress() const;
    void setAddress(int address);

// Factory..........................................
    static CodeLine* generateCodeLine(const std::string& inputLine);
};


#endif //DAY8_CODELINE_H
