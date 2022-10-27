//
// Created by Collin Morrison on 10/27/22.
//

#ifndef PROJECT_2_PARSER_HEADER_H
#define PROJECT_2_PARSER_HEADER_H

#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string> attributes;
public:
    void AddAttribute(std::string newAttribute);
};


#endif //PROJECT_2_PARSER_HEADER_H
