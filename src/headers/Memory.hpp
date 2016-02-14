#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

#pragma once

#include <vector>

//Definición de tipos
typedef *Register t_register;
typedef vector<t_register> t_memory;
typedef int t_register_value;
//

using namespace std;

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