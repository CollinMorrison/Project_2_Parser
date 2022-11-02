//
// Created by Collin Morrison on 10/27/22.
//

#ifndef PROJECT_2_PARSER_TUPLE_H
#define PROJECT_2_PARSER_TUPLE_H

#include <vector>
#include <string>

class Tuple {
private:
    std::vector<std::string> values;
public:
    bool operator< (const Tuple &rhs) const {
        return this->values < rhs.values;
    }
    void AddValue(std::string newValue);
    std::vector<std::string> GetValues ();
};


#endif //PROJECT_2_PARSER_TUPLE_H
