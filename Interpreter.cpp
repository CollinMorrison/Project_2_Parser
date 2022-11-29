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
            newTuple->AddValue(this->datalogProgram.GetFacts().at(i).GetParameters().at(j).GetValue());
        }
        //retrieve the correct relation from the database using the relation name in the fact
        Relation* correctRelation = this->database.GetRelation(this->datalogProgram.GetFacts().at(i).GetID());
        //Add the tuple to the relation in the database
        correctRelation->AddTuple(*newTuple);
        //clear newTuple
        newTuple->ClearValues();
    }
}

void Interpreter::EvaluateQueries() {
    std::string finalString;
    //for each query (relation) in the datalog program
    for (unsigned int i = 0; i < this->datalogProgram.GetQueries().size(); ++i) {
        Relation* currentRelation = EvaluatePredicate(this->datalogProgram.GetQueries().at(i));
        //print the resulting relation
        finalString += this->datalogProgram.GetQueries().at(i).ToString() + "? ";
        //if the relation is empty
        if (currentRelation->GetTuples().empty()) {
            finalString += "No\n";
        }
            //else the relation is not empty
        else {
            finalString += "Yes("
                           + std::to_string(currentRelation->GetTuples().size())
                           + ")\n";
            finalString += currentRelation->ToString();
        }
    }
    std::cout << finalString;
}

/* used to evaluate each query, and in project 4 it will be used to evaluate each
 * predicate in the body of each rule
 */
Relation* Interpreter::EvaluatePredicate(Predicate& p) {
    std::string tempVariable;
    std::vector<int> indices;
    std::vector<std::string> attributes;
    int tempIndex = 0;
    //Get the relation from the database
    Relation* currentRelation = this->database.GetRelation(p.GetID());
    //Select for each parameter
        for (unsigned int j = 0; j < p.GetParameters().size(); ++j) {
            std::string currentParameter = p.GetParameters().at(j).GetValue();
            //if the parameter is a constant
            if (currentParameter.at(0) == '\'') {
                currentRelation = currentRelation->Select(j, currentParameter);
            }
            //Select for each pair of matching variables
            else if (currentParameter == tempVariable) {
                currentRelation = currentRelation->Select(tempIndex, j);
            }
            //else save variable for verification later
            else {
                //set tempVariable in case it's a variable instead of a constant
                tempVariable = currentParameter;
                //push the index onto the indices vector
                //Check to see if the variable is already in the vector
                bool containsVariable = false;
                for (unsigned int k = 0; k < attributes.size(); ++k) {
                    if (attributes.at(k) == tempVariable) {
                        containsVariable = true;
                    }
                }
                if (!containsVariable) {
                    attributes.push_back(tempVariable);
                    indices.push_back(j);
                }
                tempIndex = j;
            }
        }
        //Project using the positions of the variables
        currentRelation = currentRelation->Project(indices);
        //rename to match the names of variables
        currentRelation = currentRelation->Rename(attributes);
        return currentRelation;
}

void Interpreter::EvaluateRules() {
    //for each rule in the datalog program
    for (unsigned int i = 0; i < this->datalogProgram.GetRules().size(); ++i) {
        //Evaluate the predicates in the body (right side)
        //Join the resulting relations
        //Project the columns that appear in the head predicate
        //Rename the relation to make it union-compatible
        //Union with the relation in the database
    }
}

void Interpreter::Print() {

}