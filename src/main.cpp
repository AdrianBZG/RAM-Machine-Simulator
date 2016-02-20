#include <cstdio>
#include <iostream>
#include <cstdlib>

//All mandatory files to include all the classes of the RAM machine simulator
#include "headers/Instruction.hpp"
#include "headers/InTape.hpp"
#include "headers/OutTape.hpp"
#include "headers/Memory.hpp"
#include "headers/Tag.hpp"
#include "headers/PC.hpp"
//

using namespace std;

int main(int argc, char **argv) {
    Instruction Ins1;
    cout << "Opcode: " << Ins1.get_opcode() << ", Mode: " << Ins1.get_mode() << ", Op: " << Ins1.get_op() << endl;
    InTape intape1;
    intape1.readFromFile();
    for(int i=0; i<intape1.getTapeSize(); i++)
        cout << intape1.read() << " ";
        
    cout << endl;
    
    OutTape outtape1;
    outtape1.write(1);
    outtape1.write(5);
    outtape1.write(3);
    outtape1.writeOnFile();
    
    Memory memory1;
    memory1.write(1,1);
    memory1.write(2,6);
    memory1.print();
    
    Tag test1("hola", 1);
    
    PC pc1;
    
}