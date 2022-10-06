#include "Lexer.h"
#include <iostream>
#include <fstream>

#include "Token.h"
#include "Parser.h"

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
    else {
        std::cout << "File is not open" << std::endl;
    }


    Lexer* lexer = new Lexer();

    lexer->Run(input);

    Parser* parser = new Parser(lexer->GetTokens());

    parser->Parse();


    delete lexer;

    return 0;
}