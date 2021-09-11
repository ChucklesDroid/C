#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define NUMBER '0'
#define SIZE 100

char operand[SIZE] ;
double stack[SIZE] ;
char buffer[SIZE] ;
char operand[SIZE] ;
int top_stack = -1 ;
int top_buffer = -1 ;
int variable[26] ;
char line[SIZE] ;
int line_index = 0 ;
static int Index = 0 ;


double getop(void)  ; 
void push(double oper) ;
int Getline( void ) ;
double pop(void) ;
int main(int argc , char *argv[])
{
    int type ;
    double op2 ;
    int flag = 0 ; 
    char var ;
    while((type = getop()) != EOF)
    {
    switch(type) 
    {
    case NUMBER :   push( atof(operand) ) ;
                    break ;
    case '+'    :   push(pop() + pop()) ;
                    stack[top_stack + 1] = '\0' ;
                    break ;
    case '-'    :   op2 = pop() ;
                    push(pop() - op2) ;
                    break ;
    case '*'    :   push(pop() * pop()) ;
                    break ;
    case '/'    :   op2 = pop() ;
                    if(op2 != 0)
                        push(pop() / op2) ;
                    else
                        printf("\n\t\tError!!.. Division by zero!!!") ;
                    break;
    case '\n'   :   printf("\n\t\tResult : %lf" , stack[top_stack]) ;
                    flag = 1 ;
                    break ;
    default     :   printf("\n\t\tError !!!..unknown command") ;
                    break;
    }
    
    if(flag == 1)
        break ;
    }
}

int Getline( void )
{
    while((line[line_index++ ] = getchar()) != '\n') ;
    line[line_index] = '\0' ;
    return line_index ;
}

double getop()
{
    if( line[line_index] == '\0')
        if(Getline() == 1) 
            return EOF ;     
    while(((operand[0] = line[ Index++ ]) == ' ' || operand[0] == '\t') && Index <= line_index ) ;
    operand[1] = '\0' ;
    if( !isdigit(operand[0]) )
        return operand[0] ;
    int oper_index = 0 ;
    while( isdigit(operand[++oper_index] = line[ Index++ ]) && Index < line_index) ;
    operand[oper_index] = '\0' ;
    if( line[Index] != EOF)
        --Index ;
    return NUMBER ;
}

void push(double oper)
{
    if(top_stack < SIZE)
        stack[++top_stack] = oper ;
    else
        printf("\n\t\tError !!.. Stack Full !!") ;
}

double pop()
{
    if(top_stack >= 0)
        return stack[top_stack--] ;
    else
        printf("\n\t\t Error !!.. Stack Empty!!") ;
}