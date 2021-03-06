/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _TAPE_HPP_
#define _TAPE_HPP_

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//Definición de tipos
typedef int t_tape_field_value;
typedef vector<t_tape_field_value> t_tape;
//

class Tape
{
    protected:
        t_tape tape_;
        string filename_;
        
    public:
        Tape();
        ~Tape();
        virtual void reset() = 0;
        int getTapeSize();
        void print();
        string getFile();
    
    protected:
        void setFile(string);
};

#endif