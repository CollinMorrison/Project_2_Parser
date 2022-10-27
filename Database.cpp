//
// Created by Collin Morrison on 10/27/22.
//

#include "Database.h"

void Database::AddRelation(std::string newString, Relation newRelation) {
    this->data.insert({newString, newRelation});
}