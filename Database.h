//
// Created by Collin Morrison on 10/27/22.
//

#ifndef PROJECT_2_PARSER_DATABASE_H
#define PROJECT_2_PARSER_DATABASE_H

#include "Relation.h"
#include <map>
#include <string>

class Database {
private:
    std::map<std::string, Relation> data;
public:
    void AddRelation(std::string newString, Relation newRelation);

};


#endif //PROJECT_2_PARSER_DATABASE_H
