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
    Predicate(std::string newID= " ", std::vector<Parameter*> newParameters = {});
    std::string ToString();
    std::vector<Parameter*> GetParameters();
};


#endif //PROJECT_2_PARSER_PREDICATE_H
