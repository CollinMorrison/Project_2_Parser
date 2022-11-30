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

std::string Header::ToString() {
    std::string finalString = "(";
    for (unsigned int i = 0; i < this->attributes.size(); ++i) {
        finalString += this->attributes.at(i)
                + ",";
    }
    finalString += ")";
    return finalString;
}

void Header::ReplaceAttributes(std::vector<std::string> newAttributes) {
    this->attributes = newAttributes;
}