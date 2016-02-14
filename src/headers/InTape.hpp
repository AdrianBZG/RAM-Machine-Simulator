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