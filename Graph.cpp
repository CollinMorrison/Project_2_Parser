//
// Created by Collin Morrison on 12/8/22.
//

#include "Graph.h"

void Graph::AddNode(int rule, std::set<int> dependees) {
        this->nodes.insert(std::pair<int, std::set<int>>(rule, dependees));
}

std::string Graph::ToString() {
    std::string finalString;
    for (std::pair<int, std::set<int>> element : this->nodes) {
        finalString += "R"
                + std::to_string(element.first)
                + ": ";
        for (int ruleNumber : element.second) {
            finalString += std::to_string(ruleNumber)
                    + ", ";
        }
        finalString += "\n";
    }
    return finalString;
}