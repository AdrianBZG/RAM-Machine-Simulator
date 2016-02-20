/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _INSTRUCTION_CPP_
#define _INSTRUCTION_CPP_

#include "headers/Instruction.hpp"

using namespace std;

//Implementations

Instruction::Instruction(void) {
    //Not defined instruction
    opcode_ = 1100;
    mode_ = 101;
    op_ = UNKNOWN_VALUE;
}

Instruction::Instruction(t_instruction_field opcode, t_instruction_field mode, t_instruction_field op) {
    opcode_ = opcode;
    mode_ = mode;
    op_ = op;
}

Instruction::~Instruction(void) {
    opcode_ = UNKNOWN_VALUE;
    mode_ = UNKNOWN_VALUE;
    op_ = UNKNOWN_VALUE;
}

t_instruction_field Instruction::get_opcode(void) {
    return opcode_;
}

t_instruction_field Instruction::get_mode(void) {
    return mode_;
}

t_instruction_field Instruction::get_op(void) {
    return op_;
}

void Instruction::alter(Instruction ins) {
    opcode_ = ins.get_opcode();
    mode_ = ins.get_mode();
    op_ = ins.get_op();
}

//
#endif