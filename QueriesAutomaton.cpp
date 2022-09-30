//
// Created by Collin Morrison on 9/20/22.
//

#include "QueriesAutomaton.h"

void QueriesAutomaton::S0(const std::string& input) {
    if (input[index] == 'Q') {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S1(const std::string& input) {
    if (input[index] == 'u') {
        index++;
        inputRead++;
        S2(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S2(const std::string& input) {
    if (input[index] == 'e') {
        index++;
        inputRead++;
        S3(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S3(const std::string& input) {
    if (input[index] == 'r') {
        index++;
        inputRead++;
        S4(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S4(const std::string& input) {
    if (input[index] == 'i') {
        index++;
        inputRead++;
        S5(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S5(const std::string& input) {
    if (input[index] == 'e') {
        index++;
        inputRead++;
        S6(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S6(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}