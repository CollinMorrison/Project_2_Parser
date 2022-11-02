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
    void AddScheme(Predicate newScheme);
    void AddFact(Predicate newFact);
    void AddQuery(Predicate newQuery);
    void AddRule(Rule newRule);
    std::vector<Predicate> GetSchemes();
    std::vector<Predicate> GetFacts();
    std::vector<Predicate> GetQueries();
};


#endif //PROJECT_2_PARSER_DATALOGPROGRAM_H
