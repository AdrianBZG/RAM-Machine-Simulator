/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
    
    Ficheros de entrada:
    1. cinta_en.txt ---> Ya esta escrito, se lee al comienzo
    2. progrram.txt ---> Cargar el programa, al comienzo
    3. cinta_sal.txt ---> Aqui se escribe al final
    
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
typedef vector<Tag> t_tags;
//

class RAMmachine
{
    private:
        Memory memory_;
        Program program_;
        InTape input_tape_;
        OutTape output_tape_;
        // Poliformismo en tiempo de ejecución
        // Tape* input_tape_;
        // Tape* output_tape_;
        // if(input_tape_ = dynamic_cast<InTape*>(input_tape_))
        // if(output_tape_ = dynamic_cast<OutTape*>(output_tape_))
        // Manejar excepciones en caso de transformacion no satisfactoria
        //
        unsigned state_; //RAM machine state -> 0 = Normal, 1 = Halt, 2 = Failed
        
    public:
        RAMmachine();
        ~RAMmachine();
        
        void initMachine(string,string,string); //To initialize the RAM machine (In file, Out file, Program file)
        void run(bool); //To start the machine, bool for verbose
        
        void printCurrentInstruction();
        void showMemoryStatus();
        void showProgram();
        void printInputTape();
        void printOutputTape();
        
    private:
    
        // Funciones para el juego de instrucciones
        void do_load();
        void do_store();
        void do_add();
        void do_sub();
        void do_mult();
        void do_div();
        void do_read();
        void do_write();
        void do_jgtz();
        void do_jzero();
        void do_halt();
        //
        
        void resetMachine(); //Reiniciar la máquina RAM (Programa + Registros + Tags + Cinta de entrada + Cinta de salida)
};

#endif