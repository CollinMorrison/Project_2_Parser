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
    std::vector<int> FindPostOrderList();
    std::set<int> DFS(std::pair<int, std::set<int>>& node, std::vector<bool>& isVisited, std::vector<int>& postOrderList);
    std::vector<std::set<int>> DFSF(std::vector<int>& postOrderList);
};


#endif //PROJECT_2_PARSER_GRAPH_H
