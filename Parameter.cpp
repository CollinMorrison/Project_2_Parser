//
// Created by Collin Morrison on 9/30/22.
//

#include "Parameter.h"

Parameter::Parameter(std::string newValue) {
    this->value = newValue;
}

std::string Parameter::GetValue() {
    return this->value;
}