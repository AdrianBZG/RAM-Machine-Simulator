/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#pragma once

#include "PC.hpp"
#include "Instruction.hpp"
#include "Tag.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctype.h>

using namespace std;


//Definición de tipos
typedef vector<Instruction> t_program;
typedef vector<Tag> t_tags;
//

class Program
{
    private:
        t_program program_;
        PC pc_;
        t_tags tags_;
        string filename_;
        
    public:
        Program();          //Program from default program file
        Program(string);
        ~Program();
        
        bool loadProgramFromFile();
        void showProgram();
        bool existTag(Tag);
        bool existTag(string);
        void moveToNextInstruction();
        void setNextInstruction(Instruction);
        t_program getProgram();
        t_tags getTags();
        PC getPC();
        void reload(string);
        void reset();
        void initPC();
        
    private:
        bool addTag(Tag);
        string getFile();
        string validateOperation(string);
        string validateMode(string);
        void processTags();
};

#endif