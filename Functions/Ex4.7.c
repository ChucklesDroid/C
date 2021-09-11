#include<stdio.h>

#define NUMBER '0'
#define SIZE 100

char operand[SIZE] ;
double stack[SIZE] ;
char buffer[SIZE] ;
char operand[SIZE] ;
int top_stack = -1 ;
int top_buffer = -1 ;
int variable[26] ;

double getop(void)  ; 
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
    case '='    :   push (variable[var - 'A'] = pop() );
                    break ;
    default     :   if(type >= 'A' && type <= 'Z')
                        var = type ; 
                    else
                        printf("\n\t\tError !!!..unknown command") ;
                    break;
    }
    
    if(flag == 1)
        break ;
    }
}

int getop()
{
    char c ;
    if( top_buffer > -1)
        return buffer[top_buffer--] ;
    while((operand[0] = c = getchar()) == ' ' || c == '\t') ;
    s[1] = '\0' ;
    if( !isdigit(c) && c != '+' && c != '-' && c != '/' && c != '*')
        return c ;
    index = 0 ;
    while(isdigit(operand[++index] = c = getchar())) ;
    if(c != EOF)
        buffer[++top_buffer] = c ;
    return NUMBER ;
}

void push(double oper)
{
    if(top_stack < SIZE)
    {
        stack[++top_stack] = oper ;
        printf("\n\t\tValue successfully pushed to the stack") ;
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