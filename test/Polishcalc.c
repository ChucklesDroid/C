// Reverse Polish Calculator
#include<stdio.h>
#include<stdlib.h>              // For atof()
#include<ctype.h>               // For isdigit()
#define MAXNO 100
#define NUMBER 0

double stack[MAXNO] ;           // Array to store numbers
char buffer[MAXNO] ;            // Array to operators temporarily 
char operand[MAXNO] ;           // Array to store and pass operand one by one
int top_stack = -1 ;            // Current Index position of the stack
int top_buffer = -1 ;           // Current index position of the buffer
int flag = 0 ;                  // indicator for breaking out of the while loop ... where value 1 represents exit from while and 0 to continue

void push(double num) ;         // For pushing value onto the stack
double pop() ;                  // For poping value from the stack and returning it
int getop() ;                   // For obtaining a numerical operand or an operand and store the extra character into buffer
int main(int argc , char *argv[])
{
    int type ;                  // Character returned from the getop() function
    int op2 ;                   // temporary variable used as second operand during division and subtraction
    while((type = getop()) != EOF)
    {
        switch(type)
        {
            case NUMBER :   push(atof(operand)) ;
                             break ;
            case '+'    :   push( pop() + pop() ) ;
                             break ;
            case '-'    :   op2 = pop() ;
                            push( pop() - op2 ) ;
                             break ;
            case '*'    :   push( pop() * pop() );
                             break ;
            case '/'    :   op2= pop() ;
                            if(op2 != 0)
                                push( pop() / op2 ) ;
                            else
                            {   printf("Division by zero !!") ;
                                flag = 1 ;}
                             break ;
            case '\n'   :   printf("\tResult:-%lf" ,stack[0]) ;
                            flag = 1;
                             break ;
            default     :   printf("\nInvalid character...") ;
                            flag = 1 ;
                             break ;
        }
        if(flag == 1)
        {   printf("\n The program will now terminate") ;
            break ;}
    }
    return 0 ;
}

int getop()                     // To get numerical operand or operator and store the extra character into buffer
{
    char ch ;                   // stores character input will be used specially for storing extra read value in the buffer array
    if(top_buffer >= 0)
        return buffer[top_buffer--] ;
    while((ch = getchar()) == ' ' || ch == '\t') ;
    if( !isdigit(ch) && ch != '.')
        return ch ;             // Not a Number
    int index_opr = 0 ;         // Index value for Storing operand for operand array
    operand[index_opr] = ch ;
    if(isdigit(ch))             // Collecting integer part
            while(isdigit(ch = operand[++index_opr] = getchar()) ) ;
    if(ch == '.')               // Collecting fractional part
            while(isdigit(ch = operand[++index_opr] = getchar()) ) ;
    operand[index_opr--] = '\0' ;// To remove the extra read character
    if(ch != EOF && ch !=' ' && ch!='\t' && top_buffer < MAXNO)
        buffer[++top_buffer] = ch ;
    return NUMBER ;       
}

void push(double num)
{
    if(top_stack < MAXNO)
        stack[++top_stack] = num ;
    else
        printf("\nStack Full!!") ;
}

double pop()
{
    if(top_stack >= 0)
        return stack[top_stack--] ;
    else
        printf("\n Stack Empty!!") ;
}