//
// Created by Collin Morrison on 9/30/22.
//

#include <string>
#include "Predicate.h"

#ifndef PROJECT_2_PARSER_RULE_H
#define PROJECT_2_PARSER_RULE_H


class Rule {
private:
    Predicate head;
    std::vector<Predicate> body;
    int identifier;
public:
    Rule();
    std::string ToString();
    void SetHead(Predicate headToSet);
    void AddToBody(Predicate itemToAdd);
    void ClearBody();
    void ClearHeadParameters();
    std::vector<Predicate> GetBody();
    Predicate GetHead();
    void SetIdentifier(int newIdentifier);
    int GetIdentifier();
};


#endif //PROJECT_2_PARSER_RULE_H
