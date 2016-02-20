/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _TAPE_CPP_
#define _TAPE_CPP_

#include "headers/Tape.hpp"

using namespace std;

//Implementations

Tape::Tape(void) {
    filename_ = "";
}

Tape::~Tape(void) {
    tape_.clear();
    filename_ = "";
}

void Tape::setFile(string fileName) {
    filename_ = fileName;
}

string Tape::getFile() {
    return filename_;
}

int Tape::getTapeSize(void) {
    return tape_.size();
}

//
#endif