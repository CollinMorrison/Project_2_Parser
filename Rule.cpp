//
// Created by Collin Morrison on 9/30/22.
//

#include "Rule.h"

std::string Rule::ToString() {
    std::string final;
    std::string list;
    for (unsigned int i = 0; i < this->body.size(); ++i) {
        list += this->body.at(i).ToString();
        if (i != (this->body.size() - 1)) {
            list += ",";
        }
    }
    final = this->head.ToString() + " :- " + list;
    return final;
}