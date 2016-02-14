/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _PC_HPP_
#define _PC_HPP_

//Definición de tipos
typedef int t_pc_value;
//

class PC
{
    private:
        t_pc_value val_;
        
    public:
        PC();
        ~PC();
        
        t_pc_value getPC();
        void setPC(t_pc_value);
};

#endif