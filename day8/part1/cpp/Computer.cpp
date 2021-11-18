//
// Created by hawk on 15.07.21.
//

#include "Computer.h"

Computer::Computer() : accumulator_(0) {}

void Computer::insertCodeLine(CodeLine *line) {
    program_.push_back(std::unique_ptr<CodeLine>(line));
}

void Computer::executeProgram() {
    int currentLine = 0;
    accumulator_ = 0;
    while (currentLine >= 0 && currentLine < program_.size() && !program_[currentLine]->isExecuted()) {
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
}

int Computer::getAccumulator() const {
    return accumulator_;
}
