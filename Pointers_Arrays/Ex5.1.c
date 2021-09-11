#include<stdio.h>
#include<ctype.h>

#define NUMBER '1'
#define SIZE 100

int stack[SIZE] ;
char buffer[SIZE] ;
int top_stack = -1 ;
int top_buffer = -1 ;
int variable[26] ;

void unGetch( int c ) ;
int Getch( void ) ;
int getint( int *pn ) ;
void push(int oper) ;
double pop(void) ;
int main(int argc , char *argv[])
{
    int type ;
    int op2 ;
    int flag = 0 ; 
    while((type = getint( stack )) != EOF)
    {
    switch(type) 
    {
    case '+'    :   push(pop() + pop()) ;
                    stack[top_stack + 1] = '\0' ;
                    break ;
    case '-'    :   op2 = pop() ;
                    push(pop() - op2) ;
                    break ;
    case '\n'   :   printf("\n\t\tResult : %lf" , stack[top_stack]) ;
                    flag = 1 ;
                    break ;
    case NUMBER :
    case '0'    :   continue ;
                    break ;
    default     :   printf("\n\t\tError !!!..unknown command") ;
                    break;
    }
    
    if(flag == 1)
        break ;
    }
}


int getint( int *pn )
{
    int sign , c ;
    while( isspace( (c = Getch()) ) ) ;
    if( !isdigit( c ) && c != '+' && c != '-')
        return 0 ;      // not a number
    sign = (c == '-' ? -1 : 1 ) ;
    if( c == '-' || c == '+' )
        c = Getch() ;
    pn += ( sizeof(int) * ( ++top_stack ) ) ;
    for ( int *pn = 0  ; isdigit( c ) ; c = Getch() )
        *pn = (((*pn) * 10) + ( c - '0')) ;   // collects integer part
    if( c == '+' || c == '-')
        unGetch( c ) ;
    *pn *= sign ;
    if( c != EOF )
        unGetch( c ) ;
    return NUMBER ;
    
}  

int Getch( void )
{
    return (top_buffer >= 0) ? buffer[ top_buffer-- ] : getchar() ;
}

void unGetch( int c ) 
{
    if ( top_buffer < SIZE )
        buffer[ ++top_buffer ] = c ;
    else
        printf("\n Too many characters in the buffer ") ;
}

void push(int oper)
{
    if(top_stack < SIZE)
    {
        stack[ ++top_stack ] = oper ;
        printf("\n\t\tValue successfully pushed to the stack") ;
    }
    else
        printf("\n\t\tError !!.. Stack Full !!") ;
}

double pop( void )
{
    if(top_stack >= 0)
        return stack[top_stack--] ;
    else
        printf("\n\t\t Error !!.. Stack Empty!!") ;
}
