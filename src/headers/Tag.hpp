#ifndef _TAG_HPP_
#define _TAG_HPP_

#include <string>

using namespace std;


//Definición de tipos
typedef unsigned t_line_number;
//

class Tag
{
    private:
        string tag_identifier_;
        t_line_number line_number_;
        
    public:
        Tag();
        Tag(string,t_line_number);
        Tag(string);
        ~Tag();
        
        string get_tag_identifier();
        t_line_number get_line_number();
        
        bool operator == (Tag&); //Sobrecarga de operador para comprobar si dos etiquetas/tags son iguales
};

#endif