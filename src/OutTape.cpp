/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _OUTTAPE_CPP_
#define _OUTTAPE_CPP_

#include "headers/OutTape.hpp"

using namespace std;

//Implementations

OutTape::OutTape(void) { }

OutTape::OutTape(string inFile) { setFile(inFile); }

OutTape::~OutTape(void) { }

void OutTape::write(t_tape_field_value value) {
    tape_.push_back(value);
}

void OutTape::reset(void) {
    tape_.clear();
}

void OutTape::writeOnFile() {
    //Here we write tape's data on the output file
    ofstream outputFile;
    outputFile.open("files/outtape_file.txt");
    if (outputFile.is_open()) {
        for(int i=0; i<getTapeSize(); i++) {
            outputFile << tape_[i] << endl;
        }
    }
    outputFile.close();
    //
}

//
#endif