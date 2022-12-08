//
// Created by Collin Morrison on 12/8/22.
//

#ifndef PROJECT_2_PARSER_GRAPH_H
#define PROJECT_2_PARSER_GRAPH_H

#include <set>
#include <map>

class Graph {
private:
    //Each node represents a rule and the rules on which it is dependent
    std::map<int, std::set<int>> nodes;

public:
    void AddNode(int rule, std::set<int> dependees);
    std::string ToString();

};


#endif //PROJECT_2_PARSER_GRAPH_H
