//
// Created by Collin Morrison on 9/20/22.
//

#ifndef PROJECT_1_LEXER_IDAUTOMATON_H
#define PROJECT_1_LEXER_IDAUTOMATON_H


#include "Automaton.h"
#include <cctype>

class IDAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IDAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_LEXER_IDAUTOMATON_H
