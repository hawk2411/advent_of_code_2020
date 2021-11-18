//
// Created by hawk on 15.07.21.
//

#include <array>
#include <sstream>

#include "CodeLine.h"

CodeLine::CodeLine(Command command, int address) {
    command_ = command;
    address_ = address;
    executed_ = false;
}

Command CodeLine::getCommand() const {
    return command_;
}

void CodeLine::setCommand(Command command) {
    command_ = command;
}

int CodeLine::getAddress() const {
    return address_;
}

void CodeLine::setAddress(int address) {
    address_ = address;
}

bool CodeLine::isExecuted() const {
    return executed_;
}

void CodeLine::setExecuted(bool executed) {
    executed_ = executed;
}

CodeLine *CodeLine::generateCodeLine(const std::string &inputLine) {
    auto pos = inputLine.find(' ');
    if(pos == std::string::npos) { return nullptr; }

    const std::array<std::string, 3> commands{"jmp", "acc", "nop"};
    const std::array<std::string, 2> parts{inputLine.substr(0, pos), inputLine.substr(pos + 1)};
    Command command;
    while(true) {
        if (parts[0] == commands[0]) {
            command = Command::JMP;
            break;
        }
        if (parts[0] == commands[1]) {
            command = Command::ACC;
            break;
        }
        if (parts[0] == commands[2]) {
            command = Command::NOP;
            break;
        }
        return nullptr;
    }
    int address = std::stoi(parts[1]);
    return new CodeLine(command, address);
}


