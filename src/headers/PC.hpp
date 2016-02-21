/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _PC_HPP_
#define _PC_HPP_

#pragma once

#include "Instruction.hpp"

//Definición de tipos
typedef Instruction t_instruction;
typedef unsigned t_line;
//

class PC
{
    private:
        t_instruction current_;
        t_line current_line_;
        
    public:
        PC();
        ~PC();
        
        t_instruction getPCinstruction();
        void setPCinstruction(t_instruction);
        t_line getCurrentLine();
        void setCurrentLine(t_line);
};

#endif