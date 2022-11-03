//
// Created by Collin Morrison on 10/27/22.
//

#ifndef PROJECT_2_PARSER_INTERPRETER_H
#define PROJECT_2_PARSER_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"


class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
public:
    Interpreter(DatalogProgram newDatalog);
    void InterpretSchemes();
    void InterpretFacts();
    void InterpretQueries();
    void EvaluateQueries();
    Relation* EvaluatePredicate(const Predicate& p);
    void Print();

};


#endif //PROJECT_2_PARSER_INTERPRETER_H
