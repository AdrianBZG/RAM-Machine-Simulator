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
typedef Instruction* t_instruction;
//

class PC
{
    private:
        t_instruction current_;
        
    public:
        PC();
        ~PC();
        
        t_instruction getPC();
        void setPC(t_instruction);
};

#endif