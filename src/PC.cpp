/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _PC_CPP_
#define _PC_CPP_

#include "headers/PC.hpp"
#include <iostream>

using namespace std;

//Implementations

PC::PC() {
    Instruction defaultEmptyIns;
    current_ = defaultEmptyIns;
    current_line_ = 0;
}

PC::~PC(void) { 
    Instruction defaultEmptyIns;
    current_ = defaultEmptyIns;
    current_line_ = 0;
}

t_instruction PC::getPCinstruction(void) {
    return current_;
}

void PC::setPCinstruction(t_instruction ins) {
    current_ = ins;
}

t_line PC::getCurrentLine(void) {
    return current_line_;
}

void PC::setCurrentLine(t_line line) {
    current_line_ = line;
}

//
#endif