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
    input_tape_.readFromFile();
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
    input_tape_.readFromFile();
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
    Instruction currentIns = program_.getPC().getPCinstruction();
    switch(stoi(currentIns.get_mode())) {
        case 001: // Immediate
            memory_.writeAccum(stoi(currentIns.get_op()));
            break;
        case 011: // Indirect
            memory_.writeAccum(memory_.read(memory_.read(stoi(currentIns.get_op()))));
            break;
        case 010: // Direct
            memory_.writeAccum(memory_.read(stoi(currentIns.get_op())));
            break;
    }
}

void RAMmachine::do_store(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    switch(stoi(currentIns.get_mode())) {
        case 001: // Immediate 
            memory_.write(stoi(currentIns.get_op()),memory_.readAccum());
            break;
        case 011: // Indirect
            memory_.write(memory_.read(memory_.read(stoi(currentIns.get_op()))),memory_.readAccum());
            break;
        case 010: // Direct
            memory_.write(memory_.read(stoi(currentIns.get_op())),memory_.readAccum());
            break;
    }
}

void RAMmachine::do_add(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    switch(stoi(currentIns.get_mode())) {
        case 001: // Immediate
            memory_.writeAccum(stoi(currentIns.get_op())+memory_.readAccum());
            break;
        case 011: // Indirect
            memory_.writeAccum(memory_.read(memory_.read(stoi(currentIns.get_op())))+memory_.readAccum());
            break;
        case 010: // Direct
            memory_.writeAccum(memory_.read(stoi(currentIns.get_op()))+memory_.readAccum());
            break;
    }
}

void RAMmachine::do_sub(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    switch(stoi(currentIns.get_mode())) {
        case 001: // Immediate
            memory_.writeAccum(stoi(currentIns.get_op())-memory_.readAccum());
            break;
        case 011: // Indirect
            memory_.writeAccum(memory_.read(memory_.read(stoi(currentIns.get_op())))-memory_.readAccum());
            break;
        case 010: // Direct
            memory_.writeAccum(memory_.read(stoi(currentIns.get_op()))-memory_.readAccum());
            break;
    }
}

void RAMmachine::do_mult(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    switch(stoi(currentIns.get_mode())) {
        case 001: // Immediate
            memory_.writeAccum(stoi(currentIns.get_op())*memory_.readAccum());
            break;
        case 011: // Indirect
            memory_.writeAccum(memory_.read(memory_.read(stoi(currentIns.get_op())))*memory_.readAccum());
            break;
        case 010: // Direct
            memory_.writeAccum(memory_.read(stoi(currentIns.get_op()))*memory_.readAccum());
            break;
    }
}

void RAMmachine::do_div(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    switch(stoi(currentIns.get_mode())) {
        case 001: // Immediate
            memory_.writeAccum(int(stoi(currentIns.get_op())/memory_.readAccum()));
            break;
        case 011: // Indirect
            memory_.writeAccum(int(memory_.read(memory_.read(stoi(currentIns.get_op())))/memory_.readAccum()));
            break;
        case 010: // Direct
            memory_.writeAccum(int(memory_.read(stoi(currentIns.get_op()))/memory_.readAccum()));
            break;
    }
}

void RAMmachine::do_read(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    switch(stoi(currentIns.get_mode())) {
        case 001: // Immediate 
            memory_.write(stoi(currentIns.get_op()),input_tape_.read());
            break;
        case 011: // Indirect
            memory_.write(memory_.read(memory_.read(stoi(currentIns.get_op()))),input_tape_.read());
            break;
        case 010: // Direct
            memory_.write(memory_.read(stoi(currentIns.get_op())),input_tape_.read());
            break;
    }
}

void RAMmachine::do_write(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    switch(stoi(currentIns.get_mode())) {
        case 001: // Immediate 
            output_tape_.write(stoi(currentIns.get_op()));
            break;
        case 011: // Indirect
            output_tape_.write(memory_.read(memory_.read(stoi(currentIns.get_op()))));
            break;
        case 010: // Direct
            output_tape_.write(memory_.read(stoi(currentIns.get_op())));
            break;
    }
}

void RAMmachine::do_jump(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    int relPos = atoi(currentIns.get_mode().c_str());
    program_.getPC().setPCinstruction(program_.getProgram()[relPos]);
}

void RAMmachine::do_jgtz(void) {
    if(memory_.read(0) > 0) {
        Instruction currentIns = program_.getPC().getPCinstruction();
        int relPos = atoi(currentIns.get_mode().c_str());
        program_.getPC().setPCinstruction(program_.getProgram()[relPos]);
    }
}

void RAMmachine::do_jzero(void) {
    if(memory_.read(0) == 0) {
        Instruction currentIns = program_.getPC().getPCinstruction();
        int relPos = atoi(currentIns.get_mode().c_str());
        program_.getPC().setPCinstruction(program_.getProgram()[relPos]);
    }
}

void RAMmachine::do_halt(void) {
    state_=1;
}

void RAMmachine::resetMachine(void) {
    program_.reset();
    memory_.reset();
    input_tape_.reset();
    output_tape_.reset();
}

//
#endif