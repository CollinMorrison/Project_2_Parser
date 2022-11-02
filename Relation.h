//
// Created by Collin Morrison on 10/27/22.
//

#ifndef PROJECT_2_PARSER_RELATION_H
#define PROJECT_2_PARSER_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>

class Relation {
private:
    std::set<Tuple> tuples;
    std::string name;
    Header header;
public:
    Relation();
    Relation(std::string newName, Header newHeader);
    Relation* Select(int index, std::string value);
    Relation* Select(int index, int nextIndex);
    //list of indices specifies the new order fo the columns in the new relation
    Relation* Project(std::vector<int> indices);
    Relation* Rename(std::vector<std::string> newAttributes);
    void AddTuple(Tuple newTuple);
    std::string ToString();
    void ReplaceHeader(Header newHeader);
};


#endif //PROJECT_2_PARSER_RELATION_H
