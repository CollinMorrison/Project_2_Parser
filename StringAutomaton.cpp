//
// Created by Collin Morrison on 9/20/22.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    while (input[index] != '\'' && input.size() > index) {
        //Check for newlines
        if (input[index] == '\n') {
            newLines++;
        }
        index++;
        inputRead++;
        //We are at EOF
        if (input.size() == index) {
            this->type = TokenType::UNDEFINED;
        }
    }
    //We are not at EOF
    if (input.size() != index) {
        index++;
        inputRead++;
        S2(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\'') {
        index++;
        inputRead++;
        S1(input);
    }
}