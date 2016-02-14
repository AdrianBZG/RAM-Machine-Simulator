/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

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
        t_program showProgram();
        bool addTag(Tag);
        bool existTag(Tag);
        Instruction run();
};

#endif