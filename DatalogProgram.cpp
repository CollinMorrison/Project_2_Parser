//
// Created by Collin Morrison on 9/30/22.
//

#include "DatalogProgram.h"
#include <iostream>
#include <set>


DatalogProgram::DatalogProgram() {

}

std::string DatalogProgram::ToString() {
    std::string final;
    std::string schemesString;
    std::string factsString;
    std::string rulesString;
    std::string queriesString;
    std::string domainString;
    std::set<std::string> domainSet;
    for (unsigned int i = 0; i < this->schemes.size(); ++i) {
        schemesString += "  ";
        schemesString += this->schemes.at(i).ToString();
        schemesString += "\n";
    }
    for (unsigned int i = 0; i < this->facts.size(); ++i) {
        factsString += "  ";
        factsString += this->facts.at(i).ToString();
        factsString += ".\n";
    }
    for (unsigned int i = 0; i < this->rules.size(); ++i) {
        rulesString += "  ";
        rulesString += this->rules.at(i).ToString();
        rulesString += ".\n";
    }
    for (unsigned int i = 0; i < this->queries.size(); ++i) {
        queriesString += "  ";
        queriesString += this->queries.at(i).ToString();
        queriesString += "?\n";
    }
    for (unsigned int i = 0; i < this->facts.size(); ++i) {
        for (unsigned int j = 0; j < this->facts.at(i).GetParameters().size(); ++j) {
            domainSet.insert(this->facts.at(i).GetParameters().at(j).GetValue());
        }
    }
    for (auto itr : domainSet) {
        domainString += "  ";
        domainString += itr;
        domainString += "\n";
    }
    final = "Schemes(" + std::to_string(schemes.size()) + "):\n"
            + schemesString
            + "Facts(" + std::to_string(facts.size()) + "):\n"
            + factsString
            + "Rules(" + std::to_string(rules.size()) + "):\n"
            + rulesString
            + "Queries(" + std::to_string(queries.size()) + "):\n"
            + queriesString
            + "Domain(" + std::to_string(domainSet.size()) + "):\n"
            + domainString;
    return final;
}

void DatalogProgram::AddScheme(Predicate newScheme) {
    this->schemes.push_back(newScheme);
}

void DatalogProgram::AddFact(Predicate newFact) {
    this->facts.push_back(newFact);
}

void DatalogProgram::AddQuery(Predicate newQuery) {
    this->queries.push_back(newQuery);
}

void DatalogProgram::AddRule(Rule newRule) {
    this->rules.push_back(newRule);
}

std::vector<Predicate> DatalogProgram::GetSchemes() {
    return this->schemes;
}

std::vector<Predicate> DatalogProgram::GetFacts() {
    return this->facts;
}