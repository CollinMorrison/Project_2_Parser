//
// Created by Collin Morrison on 9/20/22.
//

#include "RulesAutomaton.h"

void RulesAutomaton::S0(const std::string& input) {
    if (input[index] == 'R') {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S1(const std::string& input) {
    if (input[index] == 'u') {
        index++;
        inputRead++;
        S2(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S2(const std::string& input) {
    if (input[index] == 'l') {
        index++;
        inputRead++;
        S3(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S3(const std::string& input) {
    if (input[index] == 'e') {
        index++;
        inputRead++;
        S4(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S4(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}