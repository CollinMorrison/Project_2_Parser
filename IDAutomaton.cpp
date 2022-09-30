//
// Created by Collin Morrison on 9/20/22.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    //Checks if character is a letter
    if ((input[index] >= 'a' && input[index] <= 'z') || (input[index] >= 'A' && input[index] <= 'Z')) {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    while (!isspace(input[index]) && input.size() > index && (isalpha(input[index]) || isdigit(input[index]))) {
        index++;
        inputRead++;
    }
}