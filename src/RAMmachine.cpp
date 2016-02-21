/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _RAMMACHINE_CPP_
#define _RAMMACHINE_CPP_

#include "headers/RAMmachine.hpp"

using namespace std;

//Implementations

RAMmachine::RAMmachine(void) { 
    //RAMmachine with default values
    program_ = Program("files/ramprogram.ram");
    program_.initPC();
    input_tape_ = InTape("files/intape_file.in");
    output_tape_ = OutTape("files/outtape_file.out");
    memory_.reset();
}

RAMmachine::RAMmachine(string inFile, string outFile, string ramFile) { 
    initMachine(inFile,outFile,ramFile); 
}

RAMmachine::~RAMmachine(void) { 
    resetMachine();
}

void RAMmachine::initMachine(string inFile, string outFile, string ramFile) {
    program_ = Program(ramFile);
    program_.initPC();
    input_tape_ = InTape(inFile);
    output_tape_ = OutTape(outFile);
    memory_.reset();
}

void RAMmachine::printCurrentInstruction(void) {
    cout << "Current Instruction " << "\u15CC" << " ";
    Instruction currentIns = program_.getPC().getPCinstruction();
    if(currentIns.get_op() != "SALTO") {
        cout << "OPCODE: " << currentIns.get_opcode() << ", MODE: " << currentIns.get_mode() << ", OP: " << currentIns.get_op() << endl;
    } else {
        cout << "OPCODE: " << currentIns.get_opcode() << ", of type 'Jump' to line (fetched from Tag): " << currentIns.get_mode() << endl;
    }
}

void RAMmachine::showMemoryStatus(void) {
    memory_.print();
}

void RAMmachine::showProgram(void) {
    program_.showProgram();
}

void RAMmachine::printInputTape() {
    cout << "Input Tape Status: ";
    input_tape_.print();
}

void RAMmachine::printOutputTape() {
    cout << "Output Tape Status: ";
    output_tape_.print();
}

void RAMmachine::do_load(void) {
    //
}

void RAMmachine::do_store(void) {
    //
}

void RAMmachine::do_add(void) {
    //
}

void RAMmachine::do_sub(void) {
    //
}

void RAMmachine::do_mult(void) {
    //
}

void RAMmachine::do_div(void) {
    //
}

void RAMmachine::do_read(void) {
    //
}

void RAMmachine::do_write(void) {
    //
}

void RAMmachine::do_jgtz(void) {
    //
}

void RAMmachine::do_jzero(void) {
    //
}

void RAMmachine::do_halt(void) {
    //
}

void RAMmachine::resetMachine(void) {
    program_.reset();
    memory_.reset();
    input_tape_.reset();
    output_tape_.reset();
}

//
#endif