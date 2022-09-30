//
// Created by Collin Morrison on 9/20/22.
//

#ifndef PROJECT_1_LEXER_EOFAUTOMATON_H
#define PROJECT_1_LEXER_EOFAUTOMATON_H


#include "Automaton.h"

class EOFAutomaton : public Automaton
{

public:
    EOFAutomaton() : Automaton(TokenType::EOF_TYPE) {}  // Call the base constructor
};


#endif //PROJECT_1_LEXER_EOFAUTOMATON_H
