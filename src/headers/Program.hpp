#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#pragma once

#include "PC.hpp"
#include "Instruction.hpp"
#include "Tag.hpp"
#include <vector>

using namespace std;


//Definición de tipos
typedef vector<Instruction> t_program;
typedef vector<Tag> t_tags;
//

class Program
{
    private:
        t_program program_;
        PC pc_;
        t_tags tags_;
        
    public:
        Program();
        ~Program();
        
        void load_program(t_program,t_tags);
        t_program show_program();
        Instruction run();
};

#endif