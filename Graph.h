//
// Created by Collin Morrison on 12/8/22.
//

#ifndef PROJECT_2_PARSER_GRAPH_H
#define PROJECT_2_PARSER_GRAPH_H

#include <set>
#include <map>
#include "Rule.h"

class Graph {
private:
    //Each node represents a rule and the rules on which it is dependent
    std::map<int, std::set<int>> nodes;

public:
    void AddNode(int rule, std::set<int> dependees);
    std::map<int, std::set<int>> GetNodes();
    void BuildDependencyGraph(std::vector<Rule> rules);
    void BuildReverseDependencyGraph(Graph dependencyGraph);
    std::string ToString();

};


#endif //PROJECT_2_PARSER_GRAPH_H
