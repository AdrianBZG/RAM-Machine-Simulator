/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _REGISTER_CPP_
#define _REGISTER_CPP_

#include "headers/Register.hpp"

using namespace std;

//Implementations

Register::Register(void) {
    val_ = UNKNOWN_VALUE;
}

Register::Register(t_register_value value) {
    val_ = value;
}

Register::~Register(void) { 
    val_ = UNKNOWN_VALUE;
}

void Register::set_value(t_register_value value) {
    val_ = value;
}

t_register_value Register::get_value(void) {
    return val_;
}

void Register::reset(void) {
    val_ = UNKNOWN_VALUE;
}

void Register::print() {
    cout << val_ << endl;
}

//
#endif