#ifndef _RAMMACHINE_HPP_
#define _RAMMACHINE_HPP_

#pragma once

#include "Program.hpp"
#include "InTape.hpp"
#include "OutTape.hpp"
#include "Memory.hpp"

using namespace std;


//Definición de tipos
typedef int t_op;
typedef vector<Tag> t_tags;
//

class RAMmachine
{
    private:
        Memory memory_;
        Program program_;
        InTape input_tape_;
        OutTape output_tape_;
        
    public:
        RAMmachine();
        ~RAMmachine();
};

#endif