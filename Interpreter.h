//
// Created by Collin Morrison on 10/27/22.
//

#ifndef PROJECT_2_PARSER_INTERPRETER_H
#define PROJECT_2_PARSER_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"


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
    Relation* EvaluatePredicate(Predicate& p);
    void EvaluateRules();

};


#endif //PROJECT_2_PARSER_INTERPRETER_H
