//
// Created by Collin Morrison on 9/30/22.
//
#include <string>
#include <vector>
#include "Parameter.h"
#include "Token.h"

#ifndef PROJECT_2_PARSER_PREDICATE_H
#define PROJECT_2_PARSER_PREDICATE_H


class Predicate {
private:
    std::string name;
    std::vector<Parameter*> parameters;
    TokenType type;

public:
    std::string ToString();

};


#endif //PROJECT_2_PARSER_PREDICATE_H
