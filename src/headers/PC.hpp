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