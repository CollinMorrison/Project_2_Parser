//
// Created by Collin Morrison on 9/19/22.
//

#ifndef PROJECT_1_LEXER_LPARENAUTOMATON_H
#define PROJECT_1_LEXER_LPARENAUTOMATON_H

#include "Automaton.h"

class LParenAutomaton : public Automaton
{
public:
    LParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_LEXER_LPARENAUTOMATON_H
