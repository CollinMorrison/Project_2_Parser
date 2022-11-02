//
// Created by Collin Morrison on 10/27/22.
//

#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter(DatalogProgram newDatalog) {
    this->datalogProgram = newDatalog;
    InterpretSchemes();
    InterpretFacts();
}

void Interpreter::InterpretSchemes() {
    //Make a relation for each scheme and add it to the Database
    for (unsigned int i = 0; i < this->datalogProgram.GetSchemes().size(); ++i) {
        //Get list of strings from parameters attribute from the scheme list in the datalog program
        Header newHeader;
        for (unsigned int j = 0; j < this->datalogProgram.GetSchemes().at(i).GetParameters().size(); ++j) {
            //assemble Header attributes
            newHeader.AddAttribute(this->datalogProgram.GetSchemes().at(i).GetParameters().at(j).GetValue());
        }
        //create new relation
        Relation* newRelation = new Relation(this->datalogProgram.GetSchemes().at(i).GetID(), newHeader);
        //add new relation to the database map
        this->database.AddRelation(this->datalogProgram.GetSchemes().at(i).GetID(), *newRelation);
    }
}

void Interpreter::InterpretFacts() {
    //Make a tuple for each fact, and add it to the correct relation in the Database
    Tuple* newTuple = new Tuple;
    //loop over each fact
    for (unsigned int i = 0; i < this->datalogProgram.GetFacts().size(); ++i) {
        //loop over each parameter within the fact
        for (unsigned int j = 0; j < this->datalogProgram.GetFacts().at(i).GetParameters().size(); ++j) {
            //Add the individual parameter to the list of attributes within the tuple
            newTuple->AddValue(this->datalogProgram.GetFacts().at(i).GetParameters().at(i).GetValue());
        }
        //retrieve the correct relation from the database using the relation name in the fact
        Relation correctRelation = this->database.GetRelation(this->datalogProgram.GetFacts().at(i).GetID());
        //Add the tuple to the relation
        correctRelation.AddTuple(*newTuple);
        std::cout << correctRelation.ToString() << std::endl;
    }
}

void Interpreter::EvaluateQueries() {
    //for each query (relation) in the datalog program
    for (unsigned int i = 0; i < this->datalogProgram.GetQueries().size(); ++i) {
        std::string tempVariable = "";
        int tempIndex = 0;
        //Get the relation from the database
        Relation currentRelation = this->database.GetRelation(this->datalogProgram.GetQueries().at(i).GetID());
        //Select for each parameter
        for (unsigned int j = 0; j < this->datalogProgram.GetQueries().at(i).GetParameters().size(); ++j) {
            //EvaluatePredicate(const &this->datalogProgram.GetQueries().at(i).GetParameters().at(j))
            std::string currentParameter = this->datalogProgram.GetQueries().at(i).GetParameters().at(j).GetValue();
            //if the parameter is a constant
            if (currentParameter.at(0) == '\'') {
                currentRelation.Select(j, currentParameter);
            }
            //else save variable for verification later
            else {
                tempVariable = this->datalogProgram.GetQueries().at(i).GetParameters().at(j).GetValue();
                tempIndex = j;
            }
            //Select for each pair of matching variables
            if (currentParameter == tempVariable) {
                currentRelation.Select(tempIndex, j);
            }
        }

        //Project using the positions of the variables

        //rename to match the names of variables

        //print the resulting relation

    }
}

/* used to evaluate each query, and in project 4 it will be used to evaluate each
 * predicate in the body of each rule
 */
Relation* Interpreter::EvaluatePredicate(const Predicate& p) {

}