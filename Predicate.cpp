//
// Created by Collin Morrison on 9/30/22.
//

#include "Predicate.h"

std::string Predicate::ToString() {
    std::string parameterList;
    for (unsigned int i = 0; i < this->parameters.size(); ++i) {
        parameterList += this->parameters.at(i)->GetValue();
        if (i != (this->parameters.size() - 1)) {
            parameterList += ",";
        }
    }
    std::string final = this->ID + "(" + parameterList + ")";
    return final;
}