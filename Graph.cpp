//
// Created by Collin Morrison on 12/8/22.
//

#include "Graph.h"
#include <iostream>
#include <algorithm>

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

std::vector<int> Graph::FindPostOrderList() {
    std::vector<int> postOrderList;
    std::vector<bool> isVisited;
    //initialize all values in vector to false
    for (std::pair<int, std::set<int>> element : this->nodes) {
        isVisited.push_back(false);
    }
    for (std::pair<int, std::set<int>> element : this->nodes) {
        //std::cout << "Node being evaluated: R" << element.first << std::endl;
        DFS(element, isVisited, postOrderList);
    }
    return postOrderList;
}

std::set<int> Graph::DFS(std::pair<int, std::set<int>>& node1, std::vector<bool>& isVisited, std::vector<int>& postOrderList) {
    std::set<int> output;
    //set isVisited to true
    //std::cout << "node being marked as visited: R" << node1.first << std::endl;
    //std::cout << "Size of isVisited: " << isVisited.size() << std::endl;
    isVisited.at(node1.first) = true;
    //for each node adjacent to node1
    for (int nodeLabel : node1.second) {
        std::pair<int, std::set<int>> node2(nodeLabel, this->nodes.at(nodeLabel));
        //if it's not visited, go down the tree
        if (!isVisited.at(node2.first)) {
            std::set<int> result = DFS(node2, isVisited, postOrderList);
        }
    }
    if (std::find(postOrderList.begin(), postOrderList.end(), node1.first) == postOrderList.end()) {
        //std::cout << "Adding to the postorder list: R" << node1.first << std::endl;
        postOrderList.push_back(node1.first);
    }
    output.insert(node1.first);
    return output;
}

std::vector<std::set<int>> Graph::DFSF(std::vector<int>& postOrderList) {
    std::vector<std::set<int>> sccs;
    std::vector<int> empty;
    std::vector<bool> isVisited;
    //set all isVisited to false
    for (unsigned int i = 0; i < postOrderList.size(); ++i) {
        isVisited.push_back(false);
    }
    for (unsigned int i = postOrderList.size(); i > 0; --i) {
        //std::cout << "node in postorder list: R" << postOrderList.at(i - 1) << std::endl;
        std::pair<int, std::set<int>> node(postOrderList.at(i - 1), this->nodes.at(postOrderList.at(i - 1)));
        sccs.push_back(DFS(node, isVisited, postOrderList));
    }
    //std::cout << "Size of sccs: " << sccs.size() << std::endl;
    return sccs;
}

std::string Graph::ToString() {
    std::string finalString;
    for (std::pair<int, std::set<int>> element : this->nodes) {
        finalString += "R"
                + std::to_string(element.first)
                + ": ";
        for (int ruleNumber : element.second) {
            finalString += std::to_string(ruleNumber);
            auto it = element.second.end();
            it--;
            if (ruleNumber != *it) {
                finalString += ", ";
            }
        }
        finalString += "\n";
    }
    return finalString;
}