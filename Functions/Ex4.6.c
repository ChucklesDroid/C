//                                          EX 4.6( THE C PROGRAMMING BOOK )
// Add commands for handling variables. (It’s easy to provide twenty-six variables with single-letter names.)
// Add a variable for the most recently printed value 
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

int getop(void)  ; 
void push(double oper) ;
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
    case NUMBER :   push(atof(operand)) ;
                    break ;
    case '+'    :   push(pop() + pop()) ;
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
    case '='    :   pop() ;
                    variable[var - 'A'] = pop() ;
                    break ;
    default     :   if(type >= 'A' && type <= 'Z')
                        push(variable[ type - 'A']) ;
                    else
                        printf("\n\t\tError !!!..unknown command") ;
                    break;
    }
    var = type ;
    if(flag == 1)
        break ;
    }
    return 0 ;
}

int getop(void)
{
    char c ;
    if( top_buffer > -1 )
        return buffer[top_buffer--] ;
    while((operand[0] = c = getchar()) == ' ' || c == '\t') ;
    operand[1] = '\0' ;
    if( !isdigit(c) )
        return c ;
    int index = 0 ;
    while(isdigit(operand[++index] = c = getchar())) ;
    operand[index] = '\0' ;
    if(c != EOF && c != ' ' && c !='\t')
        buffer[++top_buffer] = c ;
    return NUMBER ;
}

void push(double oper)
{
    if(top_stack < SIZE)
    {
        stack[++top_stack] = oper ;
    }
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