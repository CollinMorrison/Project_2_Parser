//
// Created by Collin Morrison on 9/30/22.
//

#ifndef PROJECT_2_PARSER_PARSER_H
#define PROJECT_2_PARSER_PARSER_H
#include "DatalogProgram.h"
#include "Lexer.h"
#include "Token.h"


class Parser {
private:
    std::vector<Token*> tokens;
public:
    Parser(std::vector<Token*> inputTokens);
    DatalogProgram parse();
};


#endif //PROJECT_2_PARSER_PARSER_H
