//
// Created by Collin Morrison on 10/27/22.
//

#include "Tuple.h"

void Tuple::AddValue(std::string newValue) {
    this->values.push_back(newValue);
}

std::vector<std::string> Tuple::GetValues () {
    return this->values;
}

void Tuple::ClearValues() {
    this->values.clear();
}

std::string Tuple::ToString() {
    std::string finalString;
    for (unsigned int i = 0; i < this->values.size(); ++i) {
        finalString += this->values.at(i)
                + ", ";
    }
    return finalString;
}