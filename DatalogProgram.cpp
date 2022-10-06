//
// Created by Collin Morrison on 9/30/22.
//

#include "DatalogProgram.h"
#include <iostream>


DatalogProgram::DatalogProgram() {

}

std::string DatalogProgram::ToString() {
    std::string final;
    std::string schemesString;
    std::string factsString;
    std::string rulesString;
    std::string queriesString;
    for (unsigned int i = 0; i < this->schemes.size(); ++i) {
        schemesString += this->schemes.at(i).ToString();
        schemesString += "\n";
    }
    for (unsigned int i = 0; i < this->facts.size(); ++i) {
        factsString += this->facts.at(i).ToString();
        factsString += ".\n";
    }
    for (unsigned int i = 0; i < this->rules.size(); ++i) {
        rulesString += this->rules.at(i).ToString();
        rulesString += ".\n";
    }
    for (unsigned int i = 0; i < this->queries.size(); ++i) {
        queriesString += this->queries.at(i).ToString();
        queriesString += "?\n";
    }
    final = "Schemes(" + std::to_string(schemes.size()) + ")\n"
            + schemesString
            + "Facts(" + std::to_string(facts.size()) + ")\n"
            + factsString
            + "Rules(" + std::to_string(rules.size()) + ")\n"
            + rulesString
            + "Queries(" + std::to_string(queries.size()) + ")\n"
            + queriesString;
            //+ "Domain (" + std::to_string()
    return final;
}