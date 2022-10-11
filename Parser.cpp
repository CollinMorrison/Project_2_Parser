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
    //Set temp scheme ID
    this->tempScheme.SetID(this->currentToken->GetValue());
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    //set and push the first parameter to the temp Scheme member variable
    this->tempParameter.SetValue(this->currentToken->GetValue());
    this->tempScheme.AddParameter(this->tempParameter);
    Match(TokenType::ID);
    ParseIDList();
    //Add the temp scheme to the datalog list of schemes
    this->newDatalogProgram->AddScheme(this->tempScheme);
    ClearTempParameters();
    Match(TokenType::RIGHT_PAREN);
}

void Parser::ParseFact() {
    //Set tempFact ID
    this->tempFact.SetID(this->currentToken->GetValue());
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    //Set first fact parameter
    this->tempParameter.SetValue(this->currentToken->GetValue());
    this->tempFact.AddParameter(this->tempParameter);
    Match(TokenType::STRING);
    ParseStringList();
    //Add the tempFact to the list of facts
    this->newDatalogProgram->AddFact(this->tempFact);
    ClearTempParameters();
    Match(TokenType::RIGHT_PAREN);
    Match(TokenType::PERIOD);
}

void Parser::ParseRule() {
    ParseHeadPredicate();
    Match(TokenType::COLON_DASH);
    ParsePredicate();
    this->tempRule.AddToBody(this->tempScheme);
    ClearTempParameters();
    ParsePredicateList();
    Match(TokenType::PERIOD);
    this->newDatalogProgram->AddRule(tempRule);
    ClearTempRuleBody();
}

void Parser::ParseQuery() {
    ParsePredicate();
    Match(TokenType::Q_MARK);
    newDatalogProgram->AddQuery(this->tempScheme);
    ClearTempParameters();
}

void Parser::ParseHeadPredicate() {
    //Set tempScheme ID
    this->tempScheme.SetID(this->currentToken->GetValue());
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    //Set and push first parameter
    this->tempParameter.SetValue(this->currentToken->GetValue());
    this->tempScheme.AddParameter(this->tempParameter);
    Match(TokenType::ID);
    ParseIDList();
    //Set tempHeadPredicate
    this->tempHeadPredicate = this->tempScheme;
    this->tempRule.SetHead(tempHeadPredicate);
    ClearTempParameters();
    Match(TokenType::RIGHT_PAREN);
}

void Parser::ParsePredicate() {
    //Set tempScheme ID
    this->tempScheme.SetID(this->currentToken->GetValue());
    Match(TokenType::ID);
    Match(TokenType::LEFT_PAREN);
    ParseParameter();
    ParseParameterList();
    Match(TokenType::RIGHT_PAREN);
}

void Parser::ParsePredicateList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        Match(TokenType::COMMA);
        this->tempRule.AddToBody(this->tempScheme);
        ClearTempParameters();
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
        //Set next fact parameter
        this->tempParameter.SetValue(this->currentToken->GetValue());
        this->tempFact.AddParameter(this->tempParameter);
        Match(TokenType::STRING);
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParseStringList();
        }
    }
}

void Parser::ParseIDList() {
    if (this->currentToken->GetTokenType() == TokenType::COMMA) {
        Match(TokenType::COMMA);
        //set and push the next parameter to the temporary scheme
        this->tempParameter.SetValue(this->currentToken->GetValue());
        this->tempScheme.AddParameter(this->tempParameter);
        Match(TokenType::ID);
        if (this->currentToken->GetTokenType() == TokenType::COMMA) {
            ParseIDList();
        }
    }
}

void Parser::ParseParameter() {
    if (this->currentToken->GetTokenType() == TokenType::STRING) {
        //Add and push the parameter
        this->tempParameter.SetValue(this->currentToken->GetValue());
        this->tempScheme.AddParameter(this->tempParameter);
        Match(TokenType::STRING);
    }
    else if (this->currentToken->GetTokenType() == TokenType::ID) {
        //Add and push the parameter
        this->tempParameter.SetValue(this->currentToken->GetValue());
        this->tempScheme.AddParameter(this->tempParameter);
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

void Parser::ClearTempParameters() {
    this->tempScheme.ClearParameters();
    this->tempFact.ClearParameters();
}

void Parser::ClearTempRuleBody() {
    this->tempRule.ClearBody();
}