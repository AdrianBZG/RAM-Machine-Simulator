#ifndef _INSTRUCTION_HPP_
#define _INSTRUCTION_HPP_

#pragma once

#include <string>

using namespace std;


/* -- INFORMACIÓN --

Modos de direccionamiento:
0 = Inmediato
1 = Directo
2 = Indirecto
3 = Etiqueta de salto

Instrucciones:
0 = LOAD
1 = STORE
2 = ADD
3 = SUB
4 = MULT
5 = DIV
6 = READ
7 = WRITE
8 = JUMP
9 = JGTZ
10 = JZERO
11 = HALT

*/

//Definición de tipos
typedef unsigned t_instruction_field;
//

class Instruction
{
    private:
        t_instruction_field opcode_;
        t_instruction_field type_;
        t_instruction_field op_;
        
    public:
        Instruction();
        Instruction(t_instruction_field,t_instruction_field,t_instruction_field);
        ~Instruction();
        
        t_instruction_field get_opcode();
        t_instruction_field get_type();
        t_instruction_field get_op();
        
        void alter(Instruction);
};

#endif