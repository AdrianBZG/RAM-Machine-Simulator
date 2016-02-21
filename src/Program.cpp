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
    loadProgramFromFile();
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
    ifstream programFile;
    //Temp variables
    string str1;                //To save the entire line
    string str2;                //To save the parsed result
    string ident;               //Tag identifier found in the line
    unsigned current_line = 1;  //Line number
    //

    programFile.open(getFile());
    if (programFile.is_open()) {
        for(string str3; getline( programFile, str3 );) {
            
            // Remove commentaries ;
            size_t ocurrency = str3.find(";");
            if(ocurrency != string::npos) {
                //Found
                //Is it pos 0? (Begin of line, so it's a full line commentary)
                if(ocurrency == 0) continue; //Yes, we don't want this line
                
                //In other case
                //If before the ; was a space, we remove it
                if(isspace(str3[ocurrency-1])) {
                    str3 = string(str3, 0, ocurrency-1);
                } else { // Or not remove if it wasn't a space
                    str3 = string(str3, 0, ocurrency);
                }
            }
            str2 = str3;
            // End remove commentaries
            
            //Remove spaces or \t before the first letter
            while(isspace(str3[0]) || str3[0] == '\t') {
                str3.erase(str3.begin());
            }
            str2 = string(str3);
            //
            
            //First, let's save the instruction
            size_t ocurrencyOfTag = str2.find(":");
            string subStr1(str2.begin()+ocurrencyOfTag+1,str2.end());
            string subStr2;
            string subStr3;
            string subStr4;
            for (auto letter : subStr1) {
                if (letter != '\t') {
                    subStr2 += letter;
                }
            }
            
            ocurrency = subStr2.find(" ");
            subStr1 = string(subStr2.begin(),subStr2.begin()); //Operacion
            if(ocurrency != string::npos) //Tiene 2 elementos, por lo que debemos extraer el segundo
            {
                subStr1 = string(subStr2.begin(),subStr2.begin()+ocurrency);    //Operacion
                subStr3 = string(subStr2.begin()+ocurrency+1,subStr2.end());    //Modo+Operando
                //Remove possible spaces after the element if it was before commentaries
                string subStr3noSpaces;
                for (auto letter : subStr3) {
                    if (letter != '\t' && letter != ' ') {
                        subStr3noSpaces += letter;
                    }
                }
                subStr3 = subStr3noSpaces;
                //
                if(subStr3.length() > 1) {
                    subStr4 = string(subStr3.begin()+1,subStr3.end()); //Op if not immediate
                } else {
                    subStr4 = string(subStr3.begin(),subStr3.end()); //Op if immediate
                }
                
                //Now we can add it safely to the Program
                program_.push_back(Instruction(validateOperation(subStr1), subStr3, subStr4));
                //
            }
            else { //Tiene un solo elemento, no tiene operando
                subStr1 = subStr2;
                //Now we can add it safely to the Program
                program_.push_back(Instruction(validateOperation(subStr1), "HALT", "HALT"));
                //
            }
            
            //
            //Now we process the tag
            if(ocurrencyOfTag != string::npos) {
                //It has a tag, so we need to add it
                ident = string(str2, 0, ocurrencyOfTag);
                string insLine = string(str2.begin()+ocurrencyOfTag+1, str2.end());
                //Spaces or \t after the : ??
                string result;  //Tag
                string result2; //Instruction
                
                for (auto letter : ident)
                    if (letter != ' ' && letter != '\t')
                    result += letter;
                    
                while(isspace(insLine[0]) || insLine[0] == '\t') {
                    insLine.erase(insLine.begin());
                }
                
                ident = result;    //Tag identifier
                //Parse the instruction
                ocurrency = insLine.find(" ");
                result2 = insLine;
                if(ocurrency != string::npos) //Tiene 2 elementos, por lo que debemos extraer el segundo
                {
                    insLine = string(result2.begin(),result2.begin()+ocurrency);    //Operacion
                    subStr3 = string(result2.begin()+ocurrency+1,result2.end());    //Modo+Operando
                    //Remove possible spaces after the element if it was before commentaries
                    string subStr3noSpaces;
                    for (auto letter : subStr3) {
                        if (letter != '\t' && letter != ' ') {
                            subStr3noSpaces += letter;
                        }
                    }
                    subStr3 = subStr3noSpaces;
                    //
                    if(subStr3.length() > 1) {
                        subStr4 = string(subStr3.begin()+1,subStr3.end()); //Op if not immediate
                    } else {
                        subStr4 = string(subStr3.begin(),subStr3.end()); //Op if immediate
                    }
                
                    //Now we can add it safely to the Program
                    program_.back().alter(Instruction(validateOperation(insLine), subStr3, subStr4));
                    //
                }
                else { //Tiene un solo elemento, no tiene operando
                    insLine = subStr2;
                    string insLinenoSpaces;
                    for (auto letter : insLine) {
                        if (letter != '\t' && letter != ' ') {
                            insLinenoSpaces += letter;
                        }
                    }
                    insLine = insLinenoSpaces;
                    
                    //Now we can add it safely to the Program
                    program_.back().alter(Instruction(validateOperation(insLine), "HALT", "HALT"));
                    //
                }
                //
                //
                //Add the tag to the vector
                addTag(Tag(ident,current_line,current_line-1));
            }
            current_line++; //Incrementing the current line (relative to the file)
        }
    }
    programFile.close();
    
    //Process the Tags to set the correct line to jump in the program (Instructions) and check if they exist
    processTags();
    //
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

void Program::processTags(void) {
    bool found = false;
    for(int i=0; i<program_.size(); i++)
    {
        if(program_[i].get_opcode() == "1000" || program_[i].get_opcode() == "1001" || program_[i].get_opcode() == "1010") {
            for(int j=0; j<tags_.size(); j++) {
                if(tags_[j].get_tag_identifier() == program_[i].get_mode())
                {
                    found = true;
                    program_[i].alter(Instruction(program_[i].get_opcode(),tags_[j].get_saved_number_pos(),"SALTO"));
                }
            }
            if(!found) {
                //That Tag doesn't exist, throw exception
                
            }
        } else {
            if(program_[i].get_opcode() != "1011") {
                program_[i].alter(Instruction(program_[i].get_opcode(),validateMode(program_[i].get_mode()),program_[i].get_op()));
            } else {
                program_[i].alter(Instruction(program_[i].get_opcode(),program_[i].get_mode(),program_[i].get_op()));
            }
        }
    }
}

string Program::validateOperation(string op) {
    //To lowercase, because it doesn't if you write e.g LOAD or load
    for(int i=0; op[i]; i++) op[i] = tolower(op[i]);
    //
    if(op == "load") return "0000";
    if(op == "store") return "0001";
    if(op == "add") return "0010";
    if(op == "sub") return "0011";
    if(op == "mult") return "0100";
    if(op == "div") return "0101";
    if(op == "read") return "0110";
    if(op == "write") return "0111";
    if(op == "jump") return "1000";
    if(op == "jgtz") return "1001";
    if(op == "jzero") return "1010";
    if(op == "halt") return "1011";
    
    //Illegal operation, throw exception here
    return "-1";
    //
}

string Program::validateMode(string mo) {

    if(mo.length() > 1) {
        if(mo[0] == '=') return "001"; //Immediate mode
        if(mo[0] == '*') return "011"; //Indirect mode
    } else {
        bool isNumber = true;
        for(string::const_iterator k = mo.begin(); k!= mo.end(); k++) {
            if(!isdigit(*k)){
                isNumber = false;
                break;
            }
        }
        if(isNumber) return "010"; //Direct mode
    }
    
    //Not a number, maybe a Tag? Let's check it
    bool isaTag = existTag(mo);
    if(isaTag) {
        return "100";
    } else {
        //Tiro excepcion
    }
    
    //Manejar excepcion
    return "-1";
    //
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

void Program::setNextInstruction(Instruction ins) {
    pc_.setPCinstruction(ins);
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