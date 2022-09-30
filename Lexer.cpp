#include <iostream>
#include "Lexer.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QmarkAutomaton.h"
#include "LParenAutomaton.h"
#include "RParenAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}


/*
 * COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TYPE
 */
void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QmarkAutomaton());
    automata.push_back(new LParenAutomaton());
    automata.push_back(new RParenAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    //automata.push_back(new UndefinedAutomaton());
    //automata.push_back(new EOFAutomaton());

}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */


    int lineNumber = 1;
    int newLinesInToken = lineNumber;
    Token* newToken;
    while (input.size() > 0) {
        //update lineNumber
        while (input.size() > 0 && isspace(input.at(0))) {
            if (input.at(0) == '\n') {
                lineNumber++;
            }
            if (input.size() > 1) {
                input = input.substr(1);
            }
            else if (input.size() == 1) {
                break;
            }
        }
        int inputRead = 0;
        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);
        for (unsigned int i = 0; i < automata.size(); ++i) {
            inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        //update lineNumber
        newLinesInToken = maxAutomaton->NewLinesRead();
        //valid token
        if (maxRead > 0) {
            newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            tokens.push_back(newToken);
            lineNumber += newLinesInToken;
        }
        //Token is undefined
        else {
            maxRead = 1;
            if (!isspace(input.at(0))) {
                newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber);
                tokens.push_back(newToken);
                lineNumber += newLinesInToken;
            }
        }
        input = input.substr(0 + maxRead);
    }

    tokens.push_back(new Token(TokenType::EOF_TYPE, "", lineNumber));
    lineNumber += newLinesInToken;

    for (unsigned int i = 0; i < tokens.size(); ++i) {
        std::cout << tokens.at(i)->ToString() << std::endl;
    }
    std::cout << "Total Tokens = " << tokens.size();

}
