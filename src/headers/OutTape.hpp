/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _OUTTAPE_HPP_
#define _OUTTAPE_HPP_

#pragma once

#include "Tape.hpp"

class OutTape: public Tape
{
    public:
        OutTape();
        ~OutTape();
        
        void write(t_tape_field_value);
        void reset();
        void writeOnFile();
};

#endif