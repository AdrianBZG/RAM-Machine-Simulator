/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _PC_CPP_
#define _PC_CPP_

#include "headers/PC.hpp"

using namespace std;

//Implementations

PC::PC() {
    current_ = nullptr;
}

PC::~PC(void) { 
    delete current_;
}

t_instruction PC::getPC(void) {
    return current_;
}

void PC::setPC(t_instruction ins) {
    current_ = ins;
}

//
#endif