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
    initMachine("files/intape_file.in","files/outtape_file.out","files/ramprogram.ram"); 
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

void RAMmachine::waitForKey(void) {
    char selection = '0';
    //Ask to show memory status
    cout << "Show memory status? (y/n)" << endl;
    cin >> selection;
    if(selection=='y') {
        system("clear");
        showMemoryStatus();
    }
    //
    selection = '0';
    while(selection!='y') {
        cout << endl << "\nType 'y' to move forward to the next iteration" << endl;
        cin >> selection;
    }
    system("clear");
}

void RAMmachine::run(bool verbose) {
    while(state_==0) {
        //Verbose mode
        string vbMode;
        string vbOp;
        if(verbose) {
            system("clear");
            //Get a human-readable representation of the mode
            if(program_.getPC().getPCinstruction().get_mode() == "001") vbMode = " (Immediate Mode)";
            else if(program_.getPC().getPCinstruction().get_mode() == "010") vbMode = " (Direct Mode)";
            else if(program_.getPC().getPCinstruction().get_mode() == "011") vbMode = " (Indirect Mode)";
            //
            vbOp = program_.getPC().getPCinstruction().get_op();
        }
        //
        //Running
        if(program_.getPC().getPCinstruction().get_opcode() == "0000") { 
            do_load();
            if(verbose) {
                cout << "Executed LOAD " << vbOp << vbMode << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "0001") {
            do_store();
            if(verbose) {
                cout << "Executed STORE " << vbOp << vbMode << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "0010") {
            do_add();
            if(verbose) {
                cout << "Executed ADD " << vbOp << vbMode << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "0011") {
            do_sub();
            if(verbose) {
                cout << "Executed SUB " << vbOp << vbMode << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "0100") {
            do_mult();
            if(verbose) {
                cout << "Executed MULT " << vbOp << vbMode << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "0101") {
            do_div();
            if(verbose) {
                cout << "Executed DIV " << vbOp << vbMode << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "0110") {
            do_read();
            if(verbose) {
                cout << "Executed READ " << vbOp << vbMode << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "0111") {
            do_write();
            if(verbose) {
                cout << "Executed WRITE " << vbOp << vbMode << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "1000") {
            do_jump();
            if(verbose) {
                cout << "Executed JUMP to line " << vbMode << " (fetched from Tag)" << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "1001") {
            do_jgtz();
            if(verbose) {
                cout << "Executed JGTZ to line " << vbMode << " (fetched from Tag)" << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "1010") {
            do_jzero();
            if(verbose) {
                cout << "Executed JZERO to line " << vbMode << " (fetched from Tag)" << endl;
                waitForKey();
            }
        }
        else if(program_.getPC().getPCinstruction().get_opcode() == "1011") {
            do_halt();
            if(verbose) {
                cout << "Executed HALT" << endl;
                waitForKey();
            }
        }
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