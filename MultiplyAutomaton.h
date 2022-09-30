//
// Created by Collin Morrison on 9/19/22.
//

#ifndef PROJECT_1_LEXER_MULTIPLYAUTOMATON_H
#define PROJECT_1_LEXER_MULTIPLYAUTOMATON_H

#include "Automaton.h"

class MultiplyAutomaton : public Automaton {
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_LEXER_MULTIPLYAUTOMATON_H
