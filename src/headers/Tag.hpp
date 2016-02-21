/*
    Author: Adrián Rodríguez Bazaga
    Contact: arodriba@ull.edu.es / alu0100826456@ull.edu.es
    Date: 14/02/2016
*/

#ifndef _TAG_HPP_
#define _TAG_HPP_

#pragma once

#include <string>

using namespace std;


//Definición de tipos
typedef unsigned t_line_number;
typedef unsigned t_pos_number;
//

class Tag
{
    private:
        string tag_identifier_;
        t_line_number line_number_;
        t_pos_number saved_number_pos_;
        
    public:
        Tag(string,t_line_number,t_pos_number);
        ~Tag();
        
        string get_tag_identifier();
        t_line_number get_line_number();
        string get_saved_number_pos();
        
        bool operator == (Tag&); //Sobrecarga de operador para comprobar si dos etiquetas/tags son iguales
};

#endif