//
// Created by Collin Morrison on 9/20/22.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        index++;
        inputRead++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        index++;
        inputRead++;
        S2(input);
    }
    else {
        S3(input);
    }
}

//multi-line comment
void CommentAutomaton::S2(const std::string& input) {
    while (input[index] != '|' && input.size() > index) {
        //Check for new lines
        if (input[index] == '\n') {
            newLines++;
        }
        index++;
        inputRead++;
    }
    //We are at EOF
    if (input.size() == index) {
        this->type = TokenType::UNDEFINED;
    }
    else if (input.size() != index){
        index++;
        inputRead++;
        S4(input);
    }
}

//single-line comment
void CommentAutomaton::S3(const std::string& input) {
    while (input[index] != '\n' && input.size() > index) {
        index++;
        inputRead++;
    }
}

void CommentAutomaton::S4(const std::string& input) {
    if (input[index] == '#') {
        index++;
        inputRead++;
    }
    else {
        S2(input);
    }
}