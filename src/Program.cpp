/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _PROGRAM_CPP_
#define _PROGRAM_CPP_

#include "headers/Program.hpp"

using namespace std;

//Implementations

Program::Program(void) { 
    filename_ = "files/ramprogram.ram";
}

Program::Program(string filename) { 
    filename_ = filename;
    loadProgramFromFile();
}

Program::~Program(void) { 
    program_.clear();
    tags_.clear();
    filename_ = "";
}

bool Program::loadProgramFromFile() {
    //Here we read from file and parse the result to load the program
    
    //Temp variables
    vector<string> ins;
	ifstream file;
	string aux;
	char reader[80];
	int comment;
	int tagsymbol;
	int firstspace, firstnotspace;
	
	//Temp structures to store the instruction we find on the program file and then push them to the 'program_'
	vector<Instruction> catchedInstructions;
	Instruction dummy;
	//
	
	//Boolean var to detect errors, if it's True at the end of this func, program will end
	bool error = false; 
	//

	file.open(getFile());

	if (file.good()) {
		while (!file.eof()){ //Read until end of file
			file.getline(reader, 255); //Get the line
			aux = reader;
			comment = aux.find(";"); //Search for commentaries
		
			if (comment != string::npos)  //Commentary found, create substring without it
				aux = aux.substr(0, comment);
						
			if (aux.length() != 0 && (aux.find_first_not_of(" \t\f\v\n\r") != string::npos)) { 
			    //Result string is not empty and it has \t \f \v \n or \r
			    //\t: tab, \f: form feed, \v: vertical tab, \n: new line, \r: carriage return
				ins.push_back(aux); //Push it back
				if ((tagsymbol = ins.back().find(":")) != string::npos) {
					aux = ins.back().substr(0, tagsymbol); //Substring until : symbol
					aux.erase(remove_if(aux.begin(), aux.end(), ::isspace), aux.end()); //Remove spaces
					
					//Add the tag to the vector
					addTag(Tag(aux,ins.size(),ins.size() - 1));
					
					ins.back() = ins.back().substr(tagsymbol + 1);
				}

				ins.back().erase(0, ins.back().find_first_not_of(" \t\f\v\n\r"));
				ins.back().erase(ins.back().find_last_not_of(" \t\f\v\n\r") + 1);
			}
		}
	}
	else {
		cerr << "Error: Couldn't open the program file, exiting." << endl;
		exit(EXIT_FAILURE);
	}
	file.close();
	
	for (int i = 0; i < ins.size(); i++){
		firstspace = ins[i].find_first_of(" \t\f\v\n\r");
		
		//We validate the operation and push it to catchedInstruction if it's a valid one
		aux = ins[i].substr(0, firstspace);
		dummy.alter(Instruction("-1","-1","-1"));
		catchedInstructions.push_back(validateOperation(aux,dummy,ins[i],i));
		
		if (catchedInstructions[i].get_opcode() == "1011") {
			if (ins[i] != "HALT") {
				error = true;
				break;
			}
		}
		else if (catchedInstructions[i].get_mode() == "100") {
			firstnotspace = ins[i].find_first_not_of(" \t\f\v\n\r", firstspace);
			aux = ins[i].substr(firstnotspace);
			catchedInstructions[i].alter(Instruction(catchedInstructions[i].get_opcode(),aux,"SALTO"));
			bool isaTag = existTag(aux);
            if(isaTag) {
                for(int j=0; j<tags_.size(); j++) {
                    if(tags_[j].get_tag_identifier() == catchedInstructions[i].get_mode())
                    {
                        catchedInstructions[i].alter(Instruction(catchedInstructions[i].get_opcode(),tags_[j].get_saved_number_pos(),"SALTO"));
                    }
                }
            } else {
                error = true;
				cerr << "Error: Duplicated tag found, exiting [Line " << i << "]" << endl;
				break;
            }
		}
		else {
			firstnotspace = ins[i].find_first_not_of(" \t\f\v\n\r", firstspace);
			aux = ins[i].substr(firstnotspace);

			if (aux[0] >= 48 && aux[0] <= 57){
				if (aux.find_first_not_of("1234567890") != string::npos) {
					error = true;
					cerr << "Error: Unexpected symbol at instruction [Line " << i << "]" << endl;
					break;
				}
				catchedInstructions[i].alter(Instruction(catchedInstructions[i].get_opcode(),"010",aux));
			}
			else if (aux[0] == '*'){
				aux = aux.substr(1);
				if (aux.length() == 0 || aux.find_first_not_of("1234567890") != string::npos) {
					error = true;
					cerr << "Error: Missing register number for indirect pointing [Line " << i << "]" << endl;
					break;
				}
				catchedInstructions[i].alter(Instruction(catchedInstructions[i].get_opcode(),"011",aux));
			}
			else if (aux[0] == '=') {
				aux = aux.substr(1);
				if (aux.length() == 0 || aux.find_first_not_of("1234567890") != string::npos || catchedInstructions[i].get_opcode() == "0001" || catchedInstructions[i].get_opcode() == "0110") {
					error = true;
					cerr << "Error: Immediate Mode not allowed for instruction: " << catchedInstructions[i].get_opcode() << " [Line " << i << "]" << endl;
					break;
				}
				catchedInstructions[i].alter(Instruction(catchedInstructions[i].get_opcode(),"001",aux));
			}
			else {
				error = true;
				cerr << "Error: Op for instruction: " << catchedInstructions[i].get_opcode() << " [Line " << i << "]" << endl;
				break;
			}
		}
	}
	
	if(error) exit(EXIT_FAILURE);
	program_ = catchedInstructions;
}

void Program::showProgram(void) {
    cout << "\u15B0" << " Showing program info " << "\u15B1" << endl << endl;
    cout << "The program has " << program_.size() << " loaded instructions." << endl;
    cout << "Also, the program has " << tags_.size() << " defined tags." << endl << endl;
    cout << "The instructions are (in order of load): " << endl;
    for(int i = 0; i<program_.size(); i++) {
        if(program_[i].get_op() != "SALTO") {
            cout << "Instruction [" << i+1 << "] " << "\u15CC" << " " << program_[i].get_opcode() << ", mode: " << program_[i].get_mode() << ", op: " << program_[i].get_op() << endl;
        } else {
            cout << "Instruction [" << i+1 << "] " << "\u15CC" << " " << program_[i].get_opcode() << ", of type 'Jump' to line (fetched from Tag): " << program_[i].get_mode() << endl;
        }
    }
}

Instruction Program::validateOperation(string str,Instruction& dum, string str2, int& it) {
	
	if (str == "LOAD" || str == "load") {
		dum.alter(Instruction("0000","-1","-1"));
	}
	else if (str == "STORE" || str == "store") {
		dum.alter(Instruction("0001","-1","-1"));
	}
	else if (str == "ADD" || str == "add") {
		dum.alter(Instruction("0010","-1","-1"));
	}
	else if (str == "SUB" || str == "sub") {
		dum.alter(Instruction("0011","-1","-1"));
	}
	else if (str == "MUL" || str == "mul") {
		dum.alter(Instruction("0100","-1","-1"));
	}
	else if (str == "DIV" || str == "div") {
		dum.alter(Instruction("0101","-1","-1"));
	}
	else if (str == "READ" || str == "read") {
		dum.alter(Instruction("0110","-1","-1"));
	}
	else if (str == "WRITE" || str == "write") {
		dum.alter(Instruction("0111","-1","-1"));
	}
	else if (str == "JUMP" || str == "jump") {
		//If it's a jump, the temp Mode is 100
		dum.alter(Instruction("1000","100","-1"));
	}
	else if (str == "JGTZ" || str == "jgtz") {
		dum.alter(Instruction("1001","100","-1"));
	}
	else if (str == "JZERO" || str == "jzero") {
		dum.alter(Instruction("1010","100","-1"));
	}
	else if (str == "HALT" || str == "halt") {
		dum.alter(Instruction("1011","-1","-1"));
	}
	else {
		cerr << "Error: Unknown instruction [" << str2 << "] (Line: " << it << ")" << endl;
		exit(EXIT_FAILURE);
	}
	
	return dum;
}

bool Program::addTag(Tag tag) {
    //Comprobacion de que no exista ya
    if(existTag(tag))
    {
        //Error cargando el programa, dos etiquetas con mismo nombre: false... manejo excepcion desde afuera (load_program)
        return false;
    }
    
    //Enviar a tags_
    tags_.push_back(tag);
    return true;
}

bool Program::existTag(Tag tag) {
    //Comprobar si el Tag ya existe en tags_
    for(unsigned i=0; i<tags_.size(); i++)
        if(tags_[i] == tag) return true;
    
    return false;
}

bool Program::existTag(string tagIdentifier) {
    //Comprobar si el Tag ya existe en tags_
    for(unsigned i=0; i<tags_.size(); i++)
        if(tags_[i].get_tag_identifier() == tagIdentifier) return true;
    
    return false;
}

string Program::getFile() {
    return filename_;
}

void Program::initPC(void) {
    pc_.setPCinstruction(Instruction(program_[0].get_opcode(),program_[0].get_mode(),program_[0].get_op()));
    pc_.setCurrentLine(0);
}

t_program Program::getProgram() {
    return program_;
}

t_tags Program::getTags() {
    return tags_;
}

PC Program::getPC() {
    return pc_;
}

void Program::setNextInstruction(Instruction ins, int line) {
    pc_.setPCinstruction(ins);
    pc_.setCurrentLine(line);
}

void Program::moveToNextInstruction() {
    pc_.setCurrentLine(pc_.getCurrentLine()+1);
    pc_.setPCinstruction(program_[pc_.getCurrentLine()]);
}

void Program::reset() {
    program_.clear();
    PC defaultPC;
    pc_ = defaultPC;
    tags_.clear();
    filename_ = "";
}

void Program::reload(string filename) {
    reset();
    filename_ = filename;
    loadProgramFromFile();
}


//
#endif