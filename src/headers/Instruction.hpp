/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _INSTRUCTION_HPP_
#define _INSTRUCTION_HPP_

#pragma once

#include <string>

using namespace std;


/* -- INFORMACIÓN --

Modos de direccionamiento:
001 = Inmediato
010 = Directo
011 = Indirecto
100 = Etiqueta de salto

Instrucciones:
0000 = LOAD
0001 = STORE
0010 = ADD
0011 = SUB
0100 = MULT
0101 = DIV
0110 = READ
0111 = WRITE
1000 = JUMP
1001 = JGTZ
1010 = JZERO
1011 = HALT

*/

//Definición de tipos
typedef unsigned t_instruction_field;
//

class Instruction
{
    private:
        t_instruction_field opcode_;
        t_instruction_field mode_;
        t_instruction_field op_;
        
    public:
        Instruction();
        Instruction(t_instruction_field,t_instruction_field,t_instruction_field);
        ~Instruction();
        
        t_instruction_field get_opcode();
        t_instruction_field get_mode();
        t_instruction_field get_op();
        
        void alter(Instruction);
};

#endif