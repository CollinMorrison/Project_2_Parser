//
// Created by Collin Morrison on 9/30/22.
//

#ifndef PROJECT_2_PARSER_PARSER_H
#define PROJECT_2_PARSER_PARSER_H
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include "Lexer.h"
#include "Token.h"


class Parser {
private:
    std::vector<Token*> tokens;
    Token* currentToken;
    int iterator = 0;
public:
    Parser(std::vector<Token*> inputTokens);
    void Parse();
    void Match(TokenType type);
    DatalogProgram* ParseDatalogProgram();
    void ParseSchemeList();
    void ParseFactList();
    void ParseRuleList();
    void ParseQueryList();
    void ParseScheme();
    void ParseFact();
    void ParseRule();
    void ParseQuery();
    void ParseHeadPredicate();
    void ParsePredicate();
    void ParsePredicateList();
    void ParseParameterList();
    void ParseStringList();
    void ParseIDList();
    void ParseParameter();
};


#endif //PROJECT_2_PARSER_PARSER_H
