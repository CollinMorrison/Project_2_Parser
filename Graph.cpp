//
// Created by Collin Morrison on 12/8/22.
//

#include "Graph.h"

void Graph::AddNode(int rule, std::set<int> dependees) {
        this->nodes.insert(std::pair<int, std::set<int>>(rule, dependees));
}

std::map<int, std::set<int>> Graph::GetNodes() {
    return this->nodes;
}

/*
 * A dependency graph takes a list of rules as input and assembles a structure that associates resulting relations (headers) with
 * other rules that produce tuples for the relations that the headers depend on (body)
 *
 */
void Graph::BuildDependencyGraph(std::vector<Rule> rules) {
    std::vector<Predicate> currentBody;
    std::string currentID;
    Rule currentRule;
    std::set<int> currentDependees;

    //set the rule identifiers
    for (unsigned int i = 0; i < rules.size(); ++i) {
        rules.at(i).SetIdentifier(i);
    }

    for (unsigned int i = 0; i < rules.size(); ++i) {
        currentRule = rules.at(i);
        //std::cout << "Rule identifier: R" << currentRule.GetIdentifier() << std::endl;
        //std::cout << "  Depends on: " << std::endl;
        //obtain the set of rules that this current rule is dependent on
        //get the body of the current rule
        currentBody = rules.at(i).GetBody();
        //loop over all the predicates in the current body and all the rules
        for (unsigned int j = 0; j < currentBody.size(); ++j) {
            currentID = currentBody.at(j).GetID();
        for (unsigned int k = 0; k < rules.size(); ++k) {
            /* If the ID of the relation we're depending on in the current rule corresponds
             * to a relation we're creating tuples for in another rule, add that rule's identifier to the set
             */
            if (currentID == rules.at(k).GetHead().GetID()) {
                //std::cout << "    " << rules.at(k).GetIdentifier() << std::endl;
                currentDependees.insert(rules.at(k).GetIdentifier());
            }
        }
    }
    //create a new node for the rule
    AddNode(currentRule.GetIdentifier(), currentDependees);
    //Clear the set of dependees in preparation for the next rule
    currentDependees.clear();
    }
}

void Graph::BuildReverseDependencyGraph(Graph dependencyGraph) {
    std::set<int> currentDependees;
    int currentRuleNumber;
    //for each node in the dependency graph
    for (std::pair<int, std::set<int>> element : dependencyGraph.GetNodes()) {
        currentRuleNumber = element.first;
        //populate the set of dependees
        for (std::pair<int, std::set<int>> elementInside : dependencyGraph.GetNodes()) {
            std::set<int>::iterator it = elementInside.second.find(currentRuleNumber);
            //if the current node depends on the current rule number
            if (it != elementInside.second.end()) {
                currentDependees.insert(elementInside.first);
            }
        }
        //if the current element contains
        AddNode(currentRuleNumber, currentDependees);
        currentDependees.clear();
    }
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