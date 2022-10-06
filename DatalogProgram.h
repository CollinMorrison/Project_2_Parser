//
// Created by Collin Morrison on 9/30/22.
//

#include <string>
#include <vector>
#include "Predicate.h"
#include "Rule.h"

#ifndef PROJECT_2_PARSER_DATALOGPROGRAM_H
#define PROJECT_2_PARSER_DATALOGPROGRAM_H


class DatalogProgram {
private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
public:
    DatalogProgram();
    std::string ToString();
};


#endif //PROJECT_2_PARSER_DATALOGPROGRAM_H
