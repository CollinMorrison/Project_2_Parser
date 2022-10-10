//
// Created by Collin Morrison on 9/30/22.
//

#include <string>

#ifndef PROJECT_2_PARSER_PARAMETER_H
#define PROJECT_2_PARSER_PARAMETER_H


class Parameter {
private:
    std::string value;
public:
    explicit Parameter();
    std::string GetValue();
    void SetValue(std::string newValue);
};


#endif //PROJECT_2_PARSER_PARAMETER_H
