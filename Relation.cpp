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
    return newRelation;
}

/*
 * returns a relation with the specified indices (columns) selected
 */
Relation* Relation::Project(std::vector<int> indices) {
    Relation* newRelation = new Relation(this->name, this->header);
    //loop over tuples
    for (Tuple t : this->tuples) {
        Tuple newTuple;
        Header newHeader;
        //loop over the indices requested
        for (unsigned int i = 0; i < indices.size(); ++i) {
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


Relation* Relation::Join(Relation* otherRelation) {
    //combine headers into a new header
    Header newHeader = this->CombineHeaders(this->header, otherRelation->GetHeader());
    //TODO: not sure if the new relation needs a specific name
    //make a new relation using the expanded header
    Relation* newRelation = new Relation(this->name, newHeader);

    //for each tuple in each relation
    for (Tuple t1 : this->tuples) {
        for (Tuple t2 : otherRelation->GetTuples()) {
            if (IsJoinable(t1,t2)) {
                //join the tuples and add them to the new Relation
                newRelation->AddTuple(JoinTuples(t1,t2));
            }
        }
    }
    ClearIndicesToMatch();
    return newRelation;
}


void Relation::AddTuple(Tuple newTuple) {
    this->tuples.insert(newTuple);
}

std::string Relation::ToString() {
    std::string final;
    for (Tuple t : this->tuples) {
        final += "  ";
        for (unsigned int i = 0; i < this->header.GetAttributes().size(); ++i) {
            final += this->header.GetAttributes().at(i)
                    + "="
                    + t.GetValues().at(i);
            if (i != this->header.GetAttributes().size()-1) {
                final += ", ";
            }
            else {
                final += "\n";
            }
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
Header Relation::GetHeader() {
    return this->header;
}

Header Relation::CombineHeaders(Header firstHeader, Header secondHeader) {
    Header newHeader;
    bool attributeExists = false;
    for (unsigned int i = 0; i < firstHeader.GetAttributes().size(); ++i) {
        newHeader.AddAttribute(firstHeader.GetAttributes().at(i));
    }
    for (unsigned int i = 0; i < secondHeader.GetAttributes().size(); ++i) {
        for (unsigned int j = 0; j < firstHeader.GetAttributes().size(); ++j) {
            if (firstHeader.GetAttributes().at(j) == secondHeader.GetAttributes().at(i)) {
                attributeExists = true;
                this->indicesToMatchFirstRelation.push_back(j);
                this->indicesToMatchSecondRelation.push_back(i);
            }
        }
        if (!attributeExists) {
            newHeader.AddAttribute(secondHeader.GetAttributes().at(i));
        }
    }
    return newHeader;
}

bool Relation::IsJoinable(Tuple& t1, Tuple& t2) {
    bool isJoinable = true;
    for (unsigned int i = 0; i < this->indicesToMatchSecondRelation.size(); ++i) {
        //if any value at any of the indices doesn't match then the tuples can't be joined
        if (t1.GetValues().at(this->indicesToMatchFirstRelation.at(i)) != t2.GetValues().at(this->indicesToMatchSecondRelation.at(i))) {
            isJoinable = false;
        }
    }
    return isJoinable;
}

void Relation::ClearIndicesToMatch() {
    this->indicesToMatchFirstRelation.clear();
    this->indicesToMatchSecondRelation.clear();
}

Tuple Relation::JoinTuples(Tuple& t1, Tuple& t2) {
    Tuple newTuple;
    //Add each value from the first tuple
    for (unsigned int i = 0; i < t1.GetValues().size(); ++i) {
        newTuple.AddValue(t1.GetValues().at(i));
    }
    //for each index at which the second tuple will match
    for (unsigned int i = 0; i < this->indicesToMatchSecondRelation.size(); ++i) {
        //for each value in the second tuple
        for (unsigned int j = 0; j < t2.GetValues().size(); ++j) {
            //if the index is not one at which the tuple will match, add it to the new tuple
            if (j != indicesToMatchSecondRelation.at(i)) {
                newTuple.AddValue(t2.GetValues().at(j));
            }
        }
    }
    return newTuple;
}

void Relation::ReplaceName(std::string newName) {
    this->name = newName;
}