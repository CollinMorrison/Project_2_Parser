//
// Created by Collin Morrison on 9/19/22.
//

#include "FactsAutomaton.h"

void FactsAutomaton::S0(const std::string& input) {
    if (input[index] == 'F') {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S1(const std::string& input) {
    if (input[index] == 'a') {
        index++;
        inputRead++;
        S2(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S2(const std::string& input) {
    if (input[index] == 'c') {
        index++;
        inputRead++;
        S3(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S3(const std::string& input) {
    if (input[index] == 't') {
        index++;
        inputRead++;
        S4(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S4(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}