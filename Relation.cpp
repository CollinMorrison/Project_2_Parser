//
// Created by Collin Morrison on 10/27/22.
//

#include "Relation.h"
#include "DatalogProgram.h"

Relation::Relation(std::string newName, Header newHeader) {
    this->name = newName;
    this->header = newHeader;
}

Relation Relation::Select(int index, std::string value) {

}

Relation Relation::Select(int index, int nextIndex) {

}

Relation Relation::Project(std::vector<int> indices) {

}

Relation Relation::Rename(std::vector<std::string> newAttributes) {

}

void Relation::AddTuple(Tuple newTuple) {
    this->tuples.insert(newTuple);
}

std::string Relation::ToString() {
    std::string final;
    for (Tuple t : tuples) {
        //TODO: complete for loop
    }
    return final;
}