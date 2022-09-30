//
// Created by Collin Morrison on 9/19/22.
//

#include "SchemesAutomaton.h"

void SchemesAutomaton::S0(const std::string& input) {
    if (input[index] == 'S') {
        index ++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S1(const std::string& input) {
    if (input[index] == 'c') {
        index ++;
        inputRead++;
        S2(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S2(const std::string& input) {
    if (input[index] == 'h') {
        index ++;
        inputRead++;
        S3(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S3(const std::string& input) {
    if (input[index] == 'e') {
        index ++;
        inputRead++;
        S4(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S4(const std::string& input) {
    if (input[index] == 'm') {
        index ++;
        inputRead++;
        S5(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S5(const std::string& input) {
    if (input[index] == 'e') {
        index ++;
        inputRead++;
        S6(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S6(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}