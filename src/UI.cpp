/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _UI_CPP_
#define _UI_CPP_

#include "headers/UI.hpp"

using namespace std;

//Implementations

UI::UI(void) { 
    state_ = true;
}

UI::~UI(void) { state_ = false; }

void UI::init(void) {
    RAMmachine machine_("files/intape_file.in","files/outtape_file.out","files/test2.ram");
    state_ = true;
    
    //We ask for file data to init the RAMmachine...etc.
    string str1; //Here the input tape file
    string str2; //Here the output tape file
    string str3; //Here the program filee
    
    system("clear"); //Clean the screen
    cout << "Write the name of the Input Tape file:" << endl;
    cin >> str1;
    system("clear");
    cout << "Write the name of the Output Tape file:" << endl;
    cin >> str2;
    system("clear");
    cout << "Write the name of the Program file:" << endl;
    cin >> str3;
    system("clear"); //Clean the screen
    
    machine_ = RAMmachine(str1,str2,str3); //Now we update the machine with the new files
    //
    
    //And show the menu
    showMenu(machine_);
    //
}

void UI::waitForKey(void) { 
    char selection = '0';
    while(selection!='y') {
        cout << "\nType 'y' to go back to the menu" << endl;
        cin >> selection;
    }
    system("clear"); //Clean the screen
}

void UI::showMenu(RAMmachine machine_) {
    //Here we show the menu
    char opcion = '0';
    string str1;
    
    do {
        cout << endl << "=====================================================\n";
        cout << "RAM Machine Simulator\n";
        cout << "By Adrian Rodriguez Bazaga (https://www.github.com/AdrianBZG)\n";
        cout << "a. Show input tape\n";
        cout << "b. Show output tape\n";
        cout << "c. Show program\n";
        cout << "d. Show memory\n";
        cout << "e. Run\n";
        cout << "f. Run with trace (verbose)\n";
        cout << "g. Change input tape file (Current: " << machine_.getInputTape().getFile() << ")" << "\n";
        cout << "h. Change output tape file (Current: " << machine_.getOutputTape().getFile() << ")" << "\n";
        cout << "i. Change program file (Current: " << machine_.getProgram().getFile() << ")" << "\n";
        cout << "j. Exit\n";
        cout << "=====================================================\n";
        cout << "Choose your option >";
      

        cin >> opcion;
        switch (opcion){
            case 'a':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                machine_.printInputTape();
                waitForKey();
                break;
            case 'b':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                machine_.printOutputTape();
                waitForKey();
                break;
            case 'c':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                machine_.showProgram();
                waitForKey();
                break;
            case 'd':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                machine_.showMemoryStatus();
                waitForKey();
                break;
            case 'e':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                machine_.run(false);
                waitForKey();
                break;
            case 'f':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                machine_.run(true);
                waitForKey();
                break;
            case 'g':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                
                str1.clear();
                cout << "Write the name of the new Input Tape file:" << endl;
                cin >> str1;
                
                machine_ = RAMmachine(str1,machine_.getOutputTape().getFile(),machine_.getProgram().getFile());

                waitForKey();
                break;
            case 'h':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                
                str1.clear();
                cout << "Write the name of the new Output Tape file:" << endl;
                cin >> str1;
                
                machine_ = RAMmachine(machine_.getInputTape().getFile(),str1,machine_.getProgram().getFile());
                
                waitForKey();
                break;
            case 'i':
                cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
                system("clear"); //Clean the screen
                
                str1.clear();
                cout << "Write the name of the new Program file:" << endl;
                cin >> str1;
                
                machine_ = RAMmachine(machine_.getInputTape().getFile(),machine_.getOutputTape().getFile(),str1);
                
                waitForKey();
                break;
        }
    }while(opcion!='j');
    //
    
    system("clear"); //Clean the screen
    cout << "You have exited the program succesfully (Code 1)" << endl;
}

//
#endif