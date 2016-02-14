/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _INTAPE_HPP_
#define _INTAPE_HPP_

#pragma once

#include "Tape.hpp"

class InTape: public Tape
{
    public:
        InTape();
        ~InTape();
        
        t_tape_field_value read();
        void reset();
        void readFromFile();
};

#endif