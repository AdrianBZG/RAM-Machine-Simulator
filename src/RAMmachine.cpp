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
    state_ = 0;
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
    state_ = 0;
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
    
    if(currentIns.get_mode() == "011") memory_.writeAccum(memory_.read(memory_.read(stoi(currentIns.get_op()))));
    else if(currentIns.get_mode() == "001") memory_.writeAccum(stoi(currentIns.get_op()));
    else if(currentIns.get_mode() == "010") memory_.writeAccum(memory_.read(stoi(currentIns.get_op())));

    program_.moveToNextInstruction();
}

void RAMmachine::do_store(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();

    //Write operation has no immediate mode
    if(currentIns.get_mode() == "011") memory_.write(memory_.readAccum(),memory_.read(stoi(currentIns.get_op())));  //Indirect
    else if(currentIns.get_mode() == "010") memory_.write(memory_.readAccum(),stoi(currentIns.get_op()));           //Direct

    program_.moveToNextInstruction();
}

void RAMmachine::do_add(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    
    if(currentIns.get_mode() == "011") memory_.writeAccum(memory_.readAccum()+memory_.read(memory_.read(stoi(currentIns.get_op()))));  //Indirect
    else if(currentIns.get_mode() == "001") memory_.writeAccum(memory_.readAccum()+stoi(currentIns.get_op()));                         //Immediate
    else if(currentIns.get_mode() == "010") memory_.writeAccum(memory_.readAccum()+memory_.read(stoi(currentIns.get_op())));           //Direct
    
    program_.moveToNextInstruction();
}

void RAMmachine::do_sub(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    
    if(currentIns.get_mode() == "011") memory_.writeAccum(memory_.readAccum()-memory_.read(memory_.read(stoi(currentIns.get_op()))));  //Indirect
    else if(currentIns.get_mode() == "001") memory_.writeAccum(memory_.readAccum()-stoi(currentIns.get_op()));                         //Immediate
    else if(currentIns.get_mode() == "010") memory_.writeAccum(memory_.readAccum()-memory_.read(stoi(currentIns.get_op())));           //Direct
    
    program_.moveToNextInstruction();
}

void RAMmachine::do_mult(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();

    if(currentIns.get_mode() == "011") memory_.writeAccum(memory_.readAccum()*memory_.read(memory_.read(stoi(currentIns.get_op()))));  //Indirect
    else if(currentIns.get_mode() == "001") memory_.writeAccum(memory_.readAccum()*stoi(currentIns.get_op()));                         //Immediate
    else if(currentIns.get_mode() == "010") memory_.writeAccum(memory_.readAccum()*memory_.read(stoi(currentIns.get_op())));           //Direct
    
    program_.moveToNextInstruction();
}

void RAMmachine::do_div(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    
    if(currentIns.get_mode() == "011") memory_.writeAccum(int(memory_.readAccum()/memory_.read(memory_.read(stoi(currentIns.get_op())))));  //Indirect
    else if(currentIns.get_mode() == "001") memory_.writeAccum(int(memory_.readAccum()/stoi(currentIns.get_op())));                         //Immediate
    else if(currentIns.get_mode() == "010") memory_.writeAccum(int(memory_.readAccum()/memory_.read(stoi(currentIns.get_op()))));           //Direct
    
    program_.moveToNextInstruction();
}

void RAMmachine::do_read(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
 
    //Read operation has no immediate mode
    if(currentIns.get_mode() == "011") memory_.write(input_tape_.read(),memory_.read(stoi(currentIns.get_op())));
    else if(currentIns.get_mode() == "010") memory_.write(input_tape_.read(),stoi(currentIns.get_op()));

    program_.moveToNextInstruction();
}

void RAMmachine::do_write(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    
    if(currentIns.get_mode() == "011") output_tape_.write(memory_.read(memory_.read(stoi(currentIns.get_op()))));
    else if(currentIns.get_mode() == "001") output_tape_.write(stoi(currentIns.get_op()));
    else if(currentIns.get_mode() == "010") output_tape_.write(memory_.read(stoi(currentIns.get_op())));

    program_.moveToNextInstruction();
}

void RAMmachine::do_jump(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    int relPos = atoi(currentIns.get_mode().c_str());
    program_.getPC().setCurrentLine(relPos);
    program_.setNextInstruction(program_.getProgram()[relPos], relPos);
}

void RAMmachine::do_jgtz(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    if(memory_.read(0) > 0) {
        int relPos = atoi(currentIns.get_mode().c_str());
        program_.setNextInstruction(program_.getProgram()[relPos], relPos);
    } else {
        program_.moveToNextInstruction();
    }
}

void RAMmachine::do_jzero(void) {
    Instruction currentIns = program_.getPC().getPCinstruction();
    if(memory_.read(0) == 0) {
        int relPos = atoi(currentIns.get_mode().c_str());
        program_.setNextInstruction(program_.getProgram()[relPos],relPos);
    } else {
        program_.moveToNextInstruction();
    }
}

void RAMmachine::do_halt(void) {
    output_tape_.writeOnFile();
    state_=1;
}

void RAMmachine::run(bool verbose) {
    while(state_==0) {
        //Running
        if(program_.getPC().getPCinstruction().get_opcode() == "0000") do_load();
        else if(program_.getPC().getPCinstruction().get_opcode() == "0001") do_store();
        else if(program_.getPC().getPCinstruction().get_opcode() == "0010") do_add();
        else if(program_.getPC().getPCinstruction().get_opcode() == "0011") do_sub();
        else if(program_.getPC().getPCinstruction().get_opcode() == "0100") do_mult();
        else if(program_.getPC().getPCinstruction().get_opcode() == "0101") do_div();
        else if(program_.getPC().getPCinstruction().get_opcode() == "0110") do_read();
        else if(program_.getPC().getPCinstruction().get_opcode() == "0111") do_write();
        else if(program_.getPC().getPCinstruction().get_opcode() == "1000") do_jump();
        else if(program_.getPC().getPCinstruction().get_opcode() == "1001") do_jgtz();
        else if(program_.getPC().getPCinstruction().get_opcode() == "1010") do_jzero();
        else if(program_.getPC().getPCinstruction().get_opcode() == "1011") do_halt();
        else { 
            cerr << "Error: Unknown instruction" << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    //Failed or Halt
    if(state_==1) {
        cout << "Program exited with code 1! (Succesful)" << endl;
    } else {
        cout << "Program exited with code 2! (Failed)" << endl;
    }
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