#include "Lexer.h"
#include <iostream>
#include <fstream>

#include "Token.h"

int main(int argc, char** argv) {

    std::string fileToOpen = argv[1];
    std::string data = "";
    std::string input = "";
    std::ifstream infile;
    infile.open(fileToOpen);
    if (infile.is_open()) {
        /*Gets input character by character and adds it to input to get the entire input string*/
        while (infile.peek() != EOF) {
            data = infile.get();
            input += data;
        }
    }

    /*
     * FOR TESTING
     * Token* token = new Token(TokenType::COMMA, ",", 500);
     * std::cout << token->ToString() << std::endl;
     */


    Lexer* lexer = new Lexer();

    lexer->Run(input);


    delete lexer;

    return 0;
}