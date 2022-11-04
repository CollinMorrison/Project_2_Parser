//
// Created by Collin Morrison on 10/27/22.
//

#include "Relation.h"
#include "DatalogProgram.h"
#include <iostream>

Relation::Relation() {

}

Relation::Relation(std::string newName, Header newHeader) {
    this->name = newName;
    this->header = newHeader;
}

/*
 * returns a relation that has all tuples with the value parameter in the column that the index specifies
 */
Relation* Relation::Select(int index, std::string value) {
    Relation* newRelation = new Relation(this->name, this->header);
    //loop over tuples
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
    //std::cout << "New Relation from Select1: " << newRelation->ToString() << std::endl;
    return newRelation;
}

/*
 * returns a relation that has all tuples that have identical values in the specified indices
 */
Relation* Relation::Select(int index, int nextIndex) {
    Relation* newRelation = new Relation (this->name, this->header);
    //loop over tuples
    for (Tuple t : this->tuples) {
        //if the values at each index are identical then that tuple is added to the relation
        if (t.GetValues().at(index) == t.GetValues().at(nextIndex)) {
            newRelation->AddTuple(t);
        }
    }
    //std::cout << "New Relation from select2: " << newRelation->ToString() << std::endl;
    return newRelation;
}

/*
 * returns a relation with the specified indices (columns) selected
 */
Relation* Relation::Project(std::vector<int> indices) {
    //std::cout << "In Project" << std::endl;
    Relation* newRelation = new Relation(this->name, this->header);
    //loop over tuples
    for (Tuple t : this->tuples) {
        Tuple newTuple;
        Header newHeader;
        //loop over the indices requested
        for (unsigned int i = 0; i < indices.size(); ++i) {
            //std::cout << "Current Index: " << indices.at(i) << std::endl;
            //Add correct value from old header to new header
            newHeader.AddAttribute(this->header.GetAttributes().at(indices.at(i)));
            //Add the value at the index
            newTuple.AddValue(t.GetValues().at(indices.at(i)));
        }
        //replace the header with the new header
        newRelation->ReplaceHeader(newHeader);
        //Add the newly constructed Tuple to the new relation
        newRelation->AddTuple(newTuple);
    }
    //std::cout << "New Relation from project: " << newRelation->ToString() << std::endl;
    return newRelation;
}

Relation* Relation::Rename(std::vector<std::string> newAttributes) {
    Relation* newRelation = new Relation(this->name, this->header);
    Header newHeader;
    //loop over new attributes
    for (unsigned int i = 0; i < newAttributes.size(); ++i) {
        //populate the new header
        newHeader.AddAttribute(newAttributes.at(i));
    }
    //replace the old header with the new header
    newRelation->ReplaceHeader(newHeader);
    //fill in the tuples
    for (Tuple t : this->tuples) {
        Tuple newTuple;
        //loop over values in each tuple
        for (unsigned int i = 0; i < t.GetValues().size(); ++i) {
            newTuple.AddValue(t.GetValues().at(i));
        }
        newRelation->AddTuple(newTuple);
    }
    return newRelation;
}

void Relation::AddTuple(Tuple newTuple) {
    //std::cout << "First value of tuple to add: " << newTuple.GetValues().at(0) << std::endl;
    this->tuples.insert(newTuple);
}

std::string Relation::ToString() {
    std::string final;
    for (Tuple t : this->tuples) {
        final += "(";
        //TODO: complete for loop
        for (std::string value : t.GetValues()) {
            final += value;
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

void Relation::ReplaceHeader(Header newHeader) {
    this->header = newHeader;
}

std::set<Tuple> Relation::GetTuples() {
    return this->tuples;
}