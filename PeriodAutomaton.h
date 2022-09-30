//
// Created by Collin Morrison on 9/19/22.
//
#include "Automaton.h"

#ifndef PROJECT_1_LEXER_PERIODAUTOMATON_H
#define PROJECT_1_LEXER_PERIODAUTOMATON_H


class PeriodAutomaton : public Automaton
{
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_LEXER_PERIODAUTOMATON_H
