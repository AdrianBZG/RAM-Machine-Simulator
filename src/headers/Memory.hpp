/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

#pragma once

#include <vector>
#include "Register.hpp"

using namespace std;

//Definición de tipos
typedef *Register t_register;
typedef vector<t_register> t_memory;
typedef int t_register_value;
//

class Memory
{
    private:
        t_memory data_;
        
    public:
        Memory();
        ~Memory();
        
        void write(t_register_value,int);
        t_register_value read(int);
        void reset();
        void print();
};

#endif