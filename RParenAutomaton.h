//
// Created by Collin Morrison on 9/19/22.
//

#ifndef PROJECT_1_LEXER_RPARENAUTOMATON_H
#define PROJECT_1_LEXER_RPARENAUTOMATON_H

#include "Automaton.h"


class RParenAutomaton : public Automaton
{
public:
    RParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_LEXER_RPARENAUTOMATON_H
