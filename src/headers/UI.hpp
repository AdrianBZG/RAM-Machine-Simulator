/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _UI_HPP_
#define _UI_HPP_

#include "RAMmachine.hpp"
#include <string>
#include <iostream>

using namespace std;


class UI
{
    private:
        bool state_; //True = Active. False = Finished
        //RAMmachine machine_;
        
    public:
        UI();
        ~UI();
        
        void init();
        void showMenu(RAMmachine);
        void waitForKey();
        
        inline bool get_state() { return state_; }
        inline void flip_state() { state_=!state_; }
};

#endif