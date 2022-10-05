//
// Created by Collin Morrison on 9/30/22.
//

#include "Parser.h"
#include <iostream>

/*
 * private:
 *  tokenVector
 *
 * constructor takes a vector of tokens as a parameter and sets the tokenVector equal to the argument
 *
 * parse(){
 *  parseDatalogProgram()
 * }
 *
 * parseDatalogProgram() {
 *  match(SCHEMES)
 *  match(COLON)
 *  parseScheme()
 * }
 *
 *
 * match(expectedTerminal) {
 *  if (expectedTerminal == currentToken) {
 *      currentToken = nextToken
 *  }
 *  else {
 *      throw an exception
 *  }
 * }
 *
 * parseScheme() {
 *
 * }
 */

Parser::Parser(std::vector<Token*> inputTokens) {
    this->tokens = inputTokens;
}

DatalogProgram Parser::parse() {
    for (unsigned int i = 0; i < this->tokens.size(); ++i) {
        std::cout << tokens.at(i)->ToString();
    }
}

//Returns a DatalogProgram object, which you then traverse using recursive descent, printing out information as necessary
