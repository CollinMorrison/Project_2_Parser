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
    this->currentToken = inputTokens.at(this->iterator);
}

void Parser::Parse() {
    try {
        ParseDatalogProgram();
    } catch (Token* error) {
        std::cout << "Failure!" << std::endl << "  " << error->ToString() << std::endl;
    }
}

DatalogProgram* Parser::ParseDatalogProgram() {
    DatalogProgram* newDatalogProgram = new DatalogProgram;
    /*for (unsigned int i = 0; i < this->tokens.size(); ++i) {
        std::cout << this->tokens.at(i)->ToString() << std::endl;
    }*/
    Match(TokenType::SCHEMES);
    Match(TokenType::COLON);
    ParseScheme();
    ParseSchemeList();
    Match(TokenType::FACTS);
    Match(TokenType::COLON);
    ParseFactList();
    Match(TokenType::RULES);
    Match(TokenType::COLON);
    ParseRuleList();
    Match(TokenType::QUERIES);
    Match(TokenType::COLON);
    ParseQuery();
    ParseQueryList();
    Match(TokenType::EOF_TYPE);
    std::cout << "Success!" << std::endl;

    return newDatalogProgram;
}

void Parser::ParseSchemeList() {
    if (this->currentToken->GetTokenType() == TokenType::ID) {
        //std::cout << "At beginning of ParseSchemeList" << std::endl;
        ParseScheme();
        //the next token is an ID, which is the start of a scheme
        if (this->currentToken->GetTokenType() == TokenType::ID) {
            ParseSchemeList();
        }
    }
    //std::cout << "At end of ParseSchemeList" << std::endl;
}

void Parser::ParseFactList() {
    if (this->currentToken->GetTokenType() == TokenType::ID) {
        //std::cout << "At beginning of ParseFactList" << std::endl;
        ParseFact();
        //the next token is an ID, which is the start of a fact
        if (this->currentToken->GetTokenType() == TokenType::ID) {
            ParseFactList();
        }
    }
    //std::cout << "At end of ParseFactList" << std::endl;
}

void Parser::ParseRuleList() {
    if (this->currentToken->GetTokenType() == TokenType::ID) {
        //std::cout << "At the start of ParseRuleList" << std::endl;
        ParseRule();
        //The next token is an ID, which is the start of a Rule
        if (this->currentToken->GetTokenType() == TokenType::ID) {
            ParseRuleList();
        }
    }
    //std::cout << "At the end of ParseRuleList" << std::endl;
}

void Parser::ParseQueryList() {
    if (this->currentToken->GetTokenType() == TokenType::ID) {
        ParseQuery();
        if (this->currentToken->GetTokenType() == TokenType::ID) {
            ParseQueryList();
        }
    }
    //std::cout << "At the end of ParseQueryList" << std::endl;
}

void Parser::ParseScheme() {
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::ID);
    ParseIDList();
    Match(TokenType::RIGHT_PAREN);
    //std::cout << "At end of ParseScheme" << std::endl;
}

void Parser::ParseFact() {
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::STRING);
    ParseStringList();
    Match(TokenType::RIGHT_PAREN);
    Match(TokenType::PERIOD);
    //std::cout << "At the end of ParseFact" << std::endl;
}

void Parser::ParseRule() {
    ParseHeadPredicate();
    Match(TokenType::COLON_DASH);
    ParsePredicate();
    ParsePredicateList();
    Match(TokenType::PERIOD);
    //std::cout << "At the end of ParseRule" << std::endl;
}

void Parser::ParseQuery() {
    ParsePredicate();
    Match(TokenType::Q_MARK);
    //std::cout << "At the end of ParseQuery" << std::endl;
}

void Parser::ParseHeadPredicate() {
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::ID);
    ParseIDList();
    Match(TokenType::RIGHT_PAREN);
    //std::cout << "At the end of ParseHeadPredicate" << std::endl;
}

void Parser::ParsePredicate() {
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    ParseParameter();
    ParseParameterList();
    Match(TokenType::RIGHT_PAREN);
    //std::cout << "At the end of ParsePredicate" << std::endl;
}

void Parser::ParsePredicateList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        std::cout << "At the beginning of ParsePredicateList" << std::endl;
        Match(TokenType::COMMA);
        ParsePredicate();
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParsePredicateList();
        }
    }
    //std::cout << "At the end of ParsePredicateList"<< std::endl;
}

void Parser::ParseParameterList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        //std::cout << "At the beginning of ParseParameterList" << std::endl;
        Match(TokenType::COMMA);
        ParseParameter();
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParseParameterList();
        }
    }
    //std::cout << "At the end of ParseParameterList" << std::endl;
}

void Parser::ParseStringList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        //std::cout << "At the beginning of ParseStringList" << std::endl;
        Match(TokenType::COMMA);
        Match(TokenType::STRING);
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParseStringList();
        }
    }
    //std::cout << "At the end of ParseStringList" << std::endl;
}

void Parser::ParseIDList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        Match(TokenType::COMMA);
        Match(TokenType::ID);
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParseIDList();
        }
    }
    //std::cout << "At end of parseIDList" << std::endl;
}

void Parser::ParseParameter() {
    if (this->currentToken->GetTokenType() == TokenType::STRING) {
        Match(TokenType::STRING);
    }
    else if (this->currentToken->GetTokenType() == TokenType::ID) {
        Match(TokenType::ID);
    }
    else {
        throw this->currentToken;
    }
    //std::cout << "At the end of ParseParameter" << std::endl;
}


void Parser::Match(TokenType type) {
    //Token doesn't match grammar
    if (this->currentToken->GetTokenType() != type) {
        throw this->currentToken;
    }
    //move to the next token, unless it's the last token
    if (this->currentToken->GetTokenType() != TokenType::EOF_TYPE) {
        this->iterator++;
        this->currentToken = tokens.at(this->iterator);
    }
}
//Returns a DatalogProgram object, which you then traverse using recursive descent, printing out information as necessary
