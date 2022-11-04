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
            //std::cout << "Next Parameter: " << this->datalogProgram.GetSchemes().at(i).GetParameters().at(j).GetValue() << std::endl;
            newHeader.AddAttribute(this->datalogProgram.GetSchemes().at(i).GetParameters().at(j).GetValue());
        }
        /*for (unsigned int j = 0; j < newHeader.GetAttributes().size(); ++j) {
            std::cout << "Parameter: " << newHeader.GetAttributes().at(j) << std::endl;
        }*/
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

        /*for (unsigned int j = 0; j < newTuple->GetValues().size(); ++j) {
            std::cout << "Parameter: " << newTuple->GetValues().at(j) << std::endl;
        }*/
        //retrieve the correct relation from the database using the relation name in the fact
        Relation* correctRelation = this->database.GetRelation(this->datalogProgram.GetFacts().at(i).GetID());
        //Add the tuple to the relation in the database
        correctRelation->AddTuple(*newTuple);
    }
}

void Interpreter::EvaluateQueries() {
    std::string finalString;
    //for each query (relation) in the datalog program
    for (unsigned int i = 0; i < this->datalogProgram.GetQueries().size(); ++i) {
        /*std::cout << "Queries: " << std::endl;
        for (unsigned int j = 0; j < this->datalogProgram.GetQueries().size(); ++j) {
            std::cout << this->datalogProgram.GetQueries().at(j).ToString() << std::endl;
        }*/
        //std::cout << "Current Query: " << this->datalogProgram.GetQueries().at(i).ToString() << std::endl;
        std::string tempVariable = "";
        std::vector<int> indices;
        std::vector<std::string> attributes;
        int tempIndex = 0;
        //Get the relation from the database
        Relation* currentRelation = this->database.GetRelation(this->datalogProgram.GetQueries().at(i).GetID());
        //std::cout << "Current relation: " << currentRelation->ToString() << std::endl;
        /*std::cout << "Parameters: " << std::endl;
        for (unsigned int k = 0; k < this->datalogProgram.GetQueries().at(i).GetParameters().size(); ++k) {
            std::cout << this->datalogProgram.GetQueries().at(i).GetParameters().at(k).GetValue() << std::endl;
        }*/
        //Select for each parameter
        for (unsigned int j = 0; j < this->datalogProgram.GetQueries().at(i).GetParameters().size(); ++j) {
            std::string currentParameter = this->datalogProgram.GetQueries().at(i).GetParameters().at(j).GetValue();
           // std::cout << "Current Parameter: " << currentParameter << std::endl;
            //if the parameter is a constant
            if (currentParameter.at(0) == '\'') {
               // std::cout << "Parameter is a constant" << std::endl;
                currentRelation = currentRelation->Select(j, currentParameter);
            }
            //Select for each pair of matching variables
            else if (currentParameter == tempVariable) {
                //std::cout << "Matching pair of variables" << std::endl;
                currentRelation = currentRelation->Select(tempIndex, j);
            }
            //else save variable for verification later
            else {
                //::cout << "Parameter is a unique variable" << std::endl;
                //set tempVariable in case it's a variable instead of a constant
                tempVariable = currentParameter;
                //push the index onto the indices vector
                attributes.push_back(tempVariable);
                indices.push_back(j);
                tempIndex = j;
            }
        }
        /*std::cout << "Indices used to project: " << std::endl;
        for (unsigned int j = 0; j < indices.size(); ++j) {
            std::cout << indices.at(j) << std::endl;
        }*/
        //Project using the positions of the variables
        currentRelation = currentRelation->Project(indices);
        //std::cout << "Current Relation after Project: " << currentRelation->ToString() << std::endl;
        //rename to match the names of variables
        currentRelation = currentRelation->Rename(attributes);
        //std::cout << "Current Relation after Rename: " << currentRelation->ToString() << std::endl;
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
/*Relation* Interpreter::EvaluatePredicate(const Predicate& p) {

}*/

void Interpreter::Print() {

}