/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _INTAPE_CPP_
#define _INTAPE_CPP_

#include "headers/InTape.hpp"

using namespace std;

//Implementations

InTape::InTape(void) { tape_it_ = -1; }

InTape::InTape(string inFile) { 
    tape_it_ = -1;
    setFile(inFile);
}

InTape::~InTape(void) { tape_it_ = -1; }

t_tape_field_value InTape::read(void) {
    moveTapeForward();
    auto return_value = tape_.at(tape_it_);
    return return_value;
}

void InTape::reset(void) {
    tape_.clear();
    tape_it_ = -1;
}

void InTape::readFromFile() {
    //Here we read from file and load the tape
    ifstream inputFile;
    int value_obtained;
    inputFile.open(getFile());
    if (inputFile.good()) {
        while (!inputFile.eof()) {
            inputFile >> (int &) value_obtained;
            tape_.push_back (value_obtained);
        }
    } else {
        cerr << "Error: Couldn't open the input tape file, exiting." << endl;
		exit(EXIT_FAILURE);
    }
    inputFile.close();
    //
}

void InTape::moveTapeForward(void) {
    tape_it_++;
}

//
#endif