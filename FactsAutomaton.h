//
// Created by Collin Morrison on 9/19/22.
//

#ifndef PROJECT_1_LEXER_FACTSAUTOMATA_H
#define PROJECT_1_LEXER_FACTSAUTOMATA_H


#include "Automaton.h"

class FactsAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);

public:
    FactsAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT_1_LEXER_FACTSAUTOMATA_H
