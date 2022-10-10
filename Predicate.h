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
    std::string ID;
    std::vector<Parameter*> parameters;

public:
    Predicate();
    std::string ToString();
    std::vector<Parameter*> GetParameters();
    void SetID(std::string newID);
    void AddParameter(Parameter* newParameter);
};


#endif //PROJECT_2_PARSER_PREDICATE_H
