//
// Created by Collin Morrison on 10/27/22.
//

#include "Relation.h"
#include "DatalogProgram.h"

Relation::Relation() {

}

Relation::Relation(std::string newName, Header newHeader) {
    this->name = newName;
    this->header = newHeader;
}

Relation* Relation::Select(int index, std::string value) {
    Relation* newRelation = new Relation(this->name, this->header);
    bool containsValue = false;
    //loop over tuples at index
    for (Tuple t : this->tuples) {
        //loop over the values in each tuple
        for (unsigned int i = 0; i < t.GetValues().size(); ++i) {
            //if the tuple contains the correct value at the correct index
            if (t.GetValues().at(index) == value) {
                //Add the tuple to the new relation
                newRelation->AddTuple(t);
            }
        }
    }
    return newRelation;
}

Relation* Relation::Select(int index, int nextIndex) {

}

Relation* Relation::Project(std::vector<int> indices) {

}

Relation* Relation::Rename(std::vector<std::string> newAttributes) {

}

void Relation::AddTuple(Tuple newTuple) {
    this->tuples.insert(newTuple);
}

std::string Relation::ToString() {
    std::string final;
    for (Tuple t : this->tuples) {
        final += "(";
        //TODO: complete for loop
        for (std::string value : t.GetValues()) {
            final += "'" + value + "'";
            //If we are not at the last value, add a comma
            if (value != t.GetValues().back()) {
                final += ",";
            }
        }
        final += ")";
        //If we are not at the last tuple, add a comma
        Tuple lastTuple = *this->tuples.rbegin();
        if (t.GetValues() != lastTuple.GetValues()) {
            final += ",";
        }
    }
    return final;
}