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
    tag_identifier_ = "";
    line_number_ = 0;
}

string Tag::get_tag_identifier(void) {
    return tag_identifier_;
}

t_line_number Tag::get_line_number(void) {
    return line_number_;
}

bool Tag::operator == (Tag& o) {
    return ((get_tag_identifier() == o.get_tag_identifier()) && (get_line_number() == o.get_line_number()));
}

//
#endif