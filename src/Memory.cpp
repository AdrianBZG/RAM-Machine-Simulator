/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _MEMORY_CPP_
#define _MEMORY_CPP_

#include "headers/Memory.hpp"

using namespace std;

//Implementations

Memory::Memory(void) {
    data_.assign(32, nullptr);
}

Memory::~Memory(void) { 
    data_.clear();
}

void Memory::write(t_register_value value, int regNumber) {
    if(data_[regNumber] == nullptr)
        data_[regNumber] = new Register(value);
    else
        data_[regNumber]->set_value(value);
}

void Memory::writeAccum(t_register_value value) {
    if(data_[0] == nullptr)
        data_[0] = new Register(value);
    else
        data_[0]->set_value(value);
}

t_register_value Memory::readAccum(void) {
    return (data_[0]->get_value());
}

t_register_value Memory::read(int regNumber) {
    return (data_[regNumber]->get_value());
}

void Memory::reset(void) {
    data_.clear();
    data_.assign(32, nullptr);
}

void Memory::print() {
    cout << "\u15B0" << " Showing memory status " << "\u15B1" << endl << endl;
    for(int i = 0; i<data_.size(); i++)
        if(data_[i] == nullptr)
            cout << "R[" << i << "] " << "\u15CC" << " Empty Register" << endl;
        else
            cout << "R[" << i << "] " << "\u15CC" << " " << data_[i]->get_value() << endl;
}

//
#endif