#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define NUMBER 1
#define STACKMAX 10

char Stack[ STACKMAX ] ;
int top_stack = -1 ;
void Push( int c ) ;
int Pop( void ) ;
int main( int argc , char *argv[] )
{
    int c ;
    int op2 ;
    while( --argc ){
        if( isdigit( (int)**++argv ) ) {
            c = NUMBER ;
        }
        else {
            c =  **argv ;
        }
        switch (c)
        {
        case NUMBER: Push( atoi( *argv ) ) ;
                      break;
        case '*'   : Push( Pop() * Pop() ) ;
                      break;
        case '+'   : Push( Pop() + Pop() ) ;
                      break;
        case '-'   : op2 = Pop() ;
                     Push( op2 - Pop() ) ;
                     break ;
        default    : printf("\nExitted switch") ;
                     break;
        }
    }
    printf("\nResult = %d" , Stack[top_stack]) ;
    return 0;
}

void Push( int c )
{   
    Stack[++top_stack] = c ;
}

int Pop()
{
    return Stack[ top_stack-- ] ;
}