/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _TAPE_HPP_
#define _TAPE_HPP_

#pragma once

#include <list>
#include <string>

using namespace std;

//Definición de tipos
typedef int t_tape_field_value;
typedef list<t_tape_field_value> t_tape;
//

class Tape
{
    protected:
        t_tape tape_;
        unsigned tape_ptr_;
        string filename_;
        
    public:
        Tape();
        ~Tape();
        
        string getTapeValue();
        void tapePtrMoveForward();
        void setInputFile(string);
        virtual void reset() = 0;
};

#endif