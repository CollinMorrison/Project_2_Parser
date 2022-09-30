//
// Created by Collin Morrison on 9/19/22.
//

#ifndef PROJECT_1_LEXER_QMARKAUTOMATON_H
#define PROJECT_1_LEXER_QMARKAUTOMATON_H

#include "Automaton.h"

class QmarkAutomaton : public Automaton
{
public:
    QmarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_LEXER_QMARKAUTOMATON_H
