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
    std::vector<unsigned int> indicesToMatchFirstRelation;
    std::vector<unsigned int> indicesToMatchSecondRelation;
public:
    Relation();
    Relation(std::string newName, Header newHeader);
    Relation* Select(int index, std::string value);
    Relation* Select(int index, int nextIndex);
    //list of indices specifies the new order fo the columns in the new relation
    Relation* Project(std::vector<int> indices);
    Relation* Rename(std::vector<std::string> newAttributes);
    Relation* Join(Relation* otherRelation);
    void AddTuple(Tuple newTuple);
    std::string ToString();
    void ReplaceHeader(Header newHeader);
    std::set<Tuple> GetTuples();
    Header GetHeader();
    Header CombineHeaders(Header firstHeader, Header secondHeader);
    bool IsJoinable(Tuple& t1, Tuple& t2);
    void ClearIndicesToMatch();
    Tuple JoinTuples(Tuple& t1, Tuple& t2);
    void ReplaceName(std::string newName);
    void Union(Relation* relationToUnion);
};


#endif //PROJECT_2_PARSER_RELATION_H
