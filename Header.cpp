//
// Created by Collin Morrison on 10/27/22.
//

#include "Header.h"

void Header::AddAttribute(std::string newAttribute) {
    this->attributes.push_back(newAttribute);
}

std::vector<std::string> Header::GetAttributes() {
    return this->attributes;
}