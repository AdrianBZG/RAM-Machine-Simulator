/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _REGISTER_HPP_
#define _REGISTER_HPP_

//Definición de tipos
typedef int t_register_value;
//

class Register
{
    private:
        t_register_value val_;
        
    public:
        Register();
        ~Register();
        
        void set_value(t_register_value);
        t_register_value get_value();
        void reset();
        void print();
};

#endif