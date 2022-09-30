#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    this->type = type;
    this->value = description;
    this->lineNumber = line;
}

/*
 * returns the final string for the token
 */
std::string Token::ToString() {
    std::string tokenString = enumToString(this->type);
    return "(" + tokenString + ",\"" + this->value + "\"," + std::to_string(this->lineNumber) + ")";
}

/*
 * converts each enum value to a string
 */
std::string Token::enumToString(TokenType tokenType) {
    if (tokenType == TokenType::COMMA) {
        return "COMMA";
    }
    else if (tokenType == TokenType::PERIOD) {
        return "PERIOD";
    }
    else if (tokenType == TokenType::Q_MARK) {
        return "Q_MARK";
    }
    else if (tokenType == TokenType::LEFT_PAREN) {
        return "LEFT_PAREN";
    }
    else if (tokenType == TokenType::RIGHT_PAREN) {
        return "RIGHT_PAREN";
    }
    else if (tokenType == TokenType::COLON) {
        return "COLON";
    }
    else if (tokenType == TokenType::COLON_DASH) {
        return "COLON_DASH";
    }
    else if (tokenType == TokenType::MULTIPLY) {
        return "MULTIPLY";
    }
    else if (tokenType == TokenType::ADD) {
        return "ADD";
    }
    else if (tokenType == TokenType::SCHEMES) {
        return "SCHEMES";
    }
    else if (tokenType == TokenType::FACTS) {
        return "FACTS";
    }
    else if (tokenType == TokenType::RULES) {
        return "RULES";
    }
    else if (tokenType == TokenType::QUERIES) {
        return "QUERIES";
    }
    else if (tokenType == TokenType::ID) {
        return "ID";
    }
    else if (tokenType == TokenType::STRING) {
        return "STRING";
    }
    else if (tokenType == TokenType::COMMENT) {
        return "COMMENT";
    }
    else if (tokenType == TokenType::EOF_TYPE) {
        return "EOF";
    }
    else {
        return "UNDEFINED";
    }
}