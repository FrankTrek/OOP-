#include <iostream>
#include "Const.h"
#include "Operation.h"
#include "Operation2.h"
using namespace Computational_Graph ;



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
    Variable a(1.0f,"abcd") ;
    Placeholder b("abcd") ;
    Constant c(1.0f,"ad") ;
    Constant d(1.2f,"cd") ;
    a.debug_print() ;
    b.debug_print() ;
    c.debug_print() ;
    d.debug_print() ;
    a.Set_output_nodes(&b);
    a.Set_output_nodes(&c);
    b.Set_output_nodes(&d) ;
    a.Reset() ;
    a.debug_print();
    b.debug_print() ;
    c.debug_print() ;
    d.debug_print() ;
    return 0;
}
