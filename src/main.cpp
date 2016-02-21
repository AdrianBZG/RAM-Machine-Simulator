/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>

//Include the RAMmachine class header
#include "headers/RAMmachine.hpp"
//

using namespace std;

int main(int argc, char **argv) {
    RAMmachine ramtest("files/intape_file.in","files/outtape_file.out","files/test1.ram");
    ramtest.run(false);
    ramtest.printOutputTape();
    ramtest.printInputTape();
}