/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _TAG_CPP_
#define _TAG_CPP_

#include "headers/Tag.hpp"

using namespace std;

//Implementations

Tag::Tag(string identifier,t_line_number number) {
    tag_identifier_ = identifier;
    line_number_ = number;
}

Tag::~Tag(void) { 
    val_ = UNKNOWN_VALUE;
}

void Tag::set_value(t_register_value value) {
    val_ = value;
}

t_register_value Tag::get_value(void) {
    return val_;
}

void Tag::reset(void) {
    val_ = UNKNOWN_VALUE;
}

void Tag::print() {
    cout << val_ << endl;
}

//
#endif