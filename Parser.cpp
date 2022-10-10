//
// Created by Collin Morrison on 9/30/22.
//

#include "Parser.h"
#include <iostream>



Parser::Parser(std::vector<Token*> inputTokens) {
    this->tokens = inputTokens;
    this->currentToken = inputTokens.at(this->iterator);
}

void Parser::Parse() {
    try {
        std::cout << ParseDatalogProgram()->ToString();
    } catch (Token* error) {
        std::cout << "Failure!" << std::endl << "  " << error->ToString() << std::endl;
    }
}

DatalogProgram* Parser::ParseDatalogProgram() {
    Match(TokenType::SCHEMES);
    Match(TokenType::COLON);
    ParseScheme();
    ParseSchemeList();
    //newDatalogProgram->AddScheme();
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
        ParseScheme();
        //the next token is an ID, which is the start of a scheme
        if (this->currentToken->GetTokenType() == TokenType::ID) {
            ParseSchemeList();
        }
    }
}

void Parser::ParseFactList() {
    if (this->currentToken->GetTokenType() == TokenType::ID) {
        ParseFact();
        //the next token is an ID, which is the start of a fact
        if (this->currentToken->GetTokenType() == TokenType::ID) {
            ParseFactList();
        }
    }
}

void Parser::ParseRuleList() {
    if (this->currentToken->GetTokenType() == TokenType::ID) {
        ParseRule();
        //The next token is an ID, which is the start of a Rule
        if (this->currentToken->GetTokenType() == TokenType::ID) {
            ParseRuleList();
        }
    }
}

void Parser::ParseQueryList() {
    if (this->currentToken->GetTokenType() == TokenType::ID) {
        ParseQuery();
        if (this->currentToken->GetTokenType() == TokenType::ID) {
            ParseQueryList();
        }
    }
}

void Parser::ParseScheme() {
    this->tempScheme->SetID(this->currentToken->GetValue());
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    tempParameter->SetValue(this->currentToken->GetValue());
    this->tempScheme->AddParameter(this->tempParameter);
    Match(TokenType::ID);
    ParseIDList();
    this->newDatalogProgram->AddScheme(this->tempScheme);
    Match(TokenType::RIGHT_PAREN);
}

void Parser::ParseFact() {
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::STRING);
    ParseStringList();
    Match(TokenType::RIGHT_PAREN);
    Match(TokenType::PERIOD);
}

void Parser::ParseRule() {
    ParseHeadPredicate();
    Match(TokenType::COLON_DASH);
    ParsePredicate();
    ParsePredicateList();
    Match(TokenType::PERIOD);
}

void Parser::ParseQuery() {
    ParsePredicate();
    Match(TokenType::Q_MARK);
}

void Parser::ParseHeadPredicate() {
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::ID);
    ParseIDList();
    Match(TokenType::RIGHT_PAREN);
}

void Parser::ParsePredicate() {
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    ParseParameter();
    ParseParameterList();
    Match(TokenType::RIGHT_PAREN);
}

void Parser::ParsePredicateList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        Match(TokenType::COMMA);
        ParsePredicate();
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParsePredicateList();
        }
    }
}

void Parser::ParseParameterList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        Match(TokenType::COMMA);
        ParseParameter();
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParseParameterList();
        }
    }
}

void Parser::ParseStringList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        Match(TokenType::COMMA);
        Match(TokenType::STRING);
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParseStringList();
        }
    }
}

void Parser::ParseIDList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        Match(TokenType::COMMA);
        this->tempParameter->SetValue(this->currentToken->GetValue());
        this->tempScheme->AddParameter(this->tempParameter);
        Match(TokenType::ID);
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParseIDList();
        }
    }
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
