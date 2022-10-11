//
// Created by Collin Morrison on 9/30/22.
//
#include <iostream>
#include "Predicate.h"

Predicate::Predicate() {
}

std::string Predicate::ToString() {
    std::string parameterList;
    for (unsigned int i = 0; i < this->parameters.size(); ++i) {
        parameterList += this->parameters.at(i).GetValue();
        if (i != (this->parameters.size() - 1)) {
            parameterList += ",";
        }
    }
    std::string final = this->ID + "(" + parameterList + ")";
    return final;
}

std::vector<Parameter> Predicate::GetParameters() {
    return this->parameters;
}

void Predicate::SetID(std::string newID) {
    this->ID = newID;
}

void Predicate::AddParameter(Parameter newParameter) {
    this->parameters.push_back(newParameter);
    for (int i = 0; i < this->parameters.size(); ++i) {
        std::cout << this->parameters.at(i).GetValue() << ",";
    }
    std::cout << std::endl;
}
