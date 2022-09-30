//
// Created by Collin Morrison on 9/19/22.
//

#include "RParenAutomaton.h"

void RParenAutomaton::S0(const std::string& input) {
    if (input[index] == ')') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}