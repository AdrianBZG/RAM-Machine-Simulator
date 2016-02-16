/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _RAMMACHINE_HPP_
#define _RAMMACHINE_HPP_

#pragma once

#include "Program.hpp"
#include "InTape.hpp"
#include "OutTape.hpp"
#include "Memory.hpp"

using namespace std;


//Definición de tipos
typedef Register* t_op;
typedef vector<Tag> t_tags;
//

class RAMmachine
{
    private:
        Memory memory_;
        Program program_;
        InTape input_tape_;
        OutTape output_tape_;
        bool state_; //RAM machine state -> True = Working, False = Halt State
        
    public:
        RAMmachine();
        ~RAMmachine();
        
        void readCode(string,string,string);
        void run(bool);
        
        void printInstruction(Instruction);
        void printMemory();
        void printProgram();
        void printInputTape();
        void printOutputTape();
        
    private:
    
        // Funciones para el juego de instrucciones
        void do_load(t_op,t_op);
        void do_store(t_op,t_op);
        void do_add(t_op,t_op);
        void do_sub(t_op,t_op);
        void do_mult(t_op,t_op);
        void do_div(t_op,t_op);
        void do_read(t_op,t_op);
        void do_write(t_op,t_op);
        void do_jgtz(t_op);
        void do_jzero(t_op);
        void do_halt();
        //
        
        void resetMachine(); //Reiniciar la máquina RAM (Programa + Registros + Tags + Cinta de entrada + Cinta de salida)
};

#endif