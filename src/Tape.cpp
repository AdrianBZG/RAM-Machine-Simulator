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

void Tape::print(void) {
    cout << "[ ";
    for(int i=0; i<getTapeSize(); i++) {
        if(i==getTapeSize()-1) {
            cout << tape_[i] << " ]";
        } else {
            cout << tape_[i] << ", ";
        }
    }
    cout << endl;
}

//
#endif