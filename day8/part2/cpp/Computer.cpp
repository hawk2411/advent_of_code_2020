//
// Created by hawk on 15.07.21.
//

#include <iostream>
#include "Computer.h"

Computer::Computer() : accumulator_(0) {}

void Computer::insertCodeLine(CodeLine *line) {
    program_.push_back(std::unique_ptr<CodeLine>(line));
}

int Computer::getAccumulator() const {
    return accumulator_;
}

bool Computer::executeProgram() {
    int currentLine = 0;
    accumulator_ = 0;
    resetExecutionFlag();

    while (currentLine >= 0 && currentLine < program_.size()) {
        if (program_[currentLine]->isExecuted()) {
            std::cout << "Ended because in endless loop: " << currentLine << "\n";
            return false;
        }

        program_[currentLine]->setExecuted(true);

        switch (program_[currentLine]->getCommand()) {
            case Command::NOP:
                currentLine++;
                break;
            case Command::ACC:
                accumulator_ += program_[currentLine]->getAddress();
                currentLine++;
                break;
            case Command::JMP:
                currentLine += program_[currentLine]->getAddress();
                break;
        }
    }
    if (currentLine < 0) { return false; }
    return true;
}

bool Computer::manipulateProgram() {
    for (auto i = 0; i < program_.size(); i++) {
        switch (program_[i]->getCommand()) {

            case Command::NOP:
                program_[i]->setCommand(Command::JMP);
                if (!executeProgram()) {
                    program_[i]->setCommand(Command::NOP);
                } else {
                    std::cout << "Changed row: " << i << " NOP -> JUMP " << " address " << program_[i]->getAddress() << "\n";
                    return true;
                }
                break;
            case Command::ACC:
                break;
            case Command::JMP:
                program_[i]->setCommand(Command::NOP);
                if (!executeProgram()) {
                    program_[i]->setCommand(Command::JMP);
                } else {
                    std::cout << "Changed row: " << i << " JUMP -> NOP " << " address " << program_[i]->getAddress() << "\n";
                    return true;
                }
                break;
        }
    }
    return false;
}

void Computer::resetExecutionFlag() {
    for(auto& line : program_) {
        line->setExecuted(false);
    }
}
