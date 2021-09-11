// Reverse Polish Calculator
// Current Bug :- to use negative numbers and not intefere with subtraction
#include<stdio.h>
#include<stdlib.h>              // For atof() and exit()
#include<ctype.h>               // For isdigit()
#include<math.h>                // For fmod() , pow , exp , trigno functions and macros :- ERANGE and EDOM
#include<errno.h>               // To check for error number by making use of macro 'errno'
#include<string.h>              // For using in Mathfunc() to calculate cos ,sin and exp functions

#define MAXNO 100
#define NUMBER '0'              // Indicating a number is read so as to push it onto the stack
#define SIN '1'                 // For using sing Function
#define COS '2'                 // For using cos Function
#define EXP '3'                 // For using exponent function
#define POW '4'                 // For using power function

double stack[MAXNO] ;           // Array to store numbers
char buffer[MAXNO] ;            // Array to operators temporarily 
char operand[MAXNO] ;           // Array to store and pass operand one by one
int top_stack = -1 ;            // Current Index position of the stack
int top_buffer = -1 ;           // Current index position of the buffer
int flag = 0 ;                  // indicator for breaking out of the while loop ... where value 1 represents exit from while and 0 to continue

void Polish_calc() ;            // Regular Polish Notation Calculator
void push(double num) ;         // For pushing value onto the stack
int Mathfunc(char ch[3]) ;      // For caculating Sin , Cos and Exponent values
double pop() ;                  // For poping value from the stack and returning it
int getop() ;                   // For obtaining a numerical operand or an operand and store the extra character into buffer

int main(int argc , char *argv[])
{
    int choic_whil ;            // Variable that determines wether while loop present in the main() is operable or exit 
    while(1)
    {
    printf("\n\n\t\t**--Reverse Polish Notation Calculator--**\n") ;
    printf("\t\t1)Print top element of the stack\n") ;
    printf("\t\t2)Duplicate the top element of the stack\n") ;
    printf("\t\t3)Swap top two elements of the stack\n") ;
    printf("\t\t4)Clear the stack\n") ;
    printf("\t\t5)Regular Reverse Polish Calculator\n") ;
    printf("\t\t6)Exit\n") ;
    scanf("%d%*c", &choic_whil ) ;

        switch (choic_whil)
        {
        case 1: if(top_stack > 0)
                 printf("\n\t\tTop Element of the stack : %lf" , stack[top_stack]) ;
                else
                { 
                    printf("\n\t\tStack is empty!!!") ;
                    exit(0) ; }
            break;
        case 2: if(top_stack >= 0)  // Arguments are evaluated from right to left according to c standard
                {   stack[top_stack + 1] = stack[top_stack ] ;
                    top_stack ++ ;
                    printf("\n\t\tSuccessfully duplicated!!") ; }
                else
                {   printf("\n\t\tStack Empty!!") ;
                    exit(0) ; }
            break;
        case 3: if(top_stack >= 1)
                {
                    printf("\n\t\tTop two elements in the stack in order are : %lf & %lf" , stack[top_stack] , stack[top_stack - 1]) ;
                    stack[top_stack] += stack[top_stack - 1] ;
                    stack[top_stack - 1] = stack[top_stack] - stack[top_stack - 1] ;
                    stack[top_stack] = stack[top_stack] - stack[top_stack - 1] ;
                    printf("\n\t\tTop two elements in the stack in order after swapping are : %lf & %lf" , stack[top_stack] , stack[top_stack - 1]) ; 
                }
                else
                {   printf("\n\t\tError!! Insufficient elements in the stack") ;
                    exit(0) ; }
            break;
        case 4: if(top_stack >= 0)
                {   stack[0] = '\0' ;
                    top_stack = -1 ; 
                    printf("\n\t\tStack Cleared") ; }
                else
                {   printf("\n\t\tStack is already empty") ;
                    exit(0) ;}
            break;
        case 5: Polish_calc() ;
            break;      
        case 6: exit(0) ;
            break;
        default : printf("\n\t\tError Encountered!! Enter a numerical value") ;
            break;
        }

    }  
    return 0 ;   
}


void Polish_calc()
{
    int type ;                  // Character returned from the getop() function
    double op2 ;                // temporary variable used as second operand during division and subtraction
    printf("\n\t\tEnter expression : ") ;
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
            case '\n'   :   printf("\t\tResult:= %lf" ,stack[0]) ;
                            flag = 1;
                             break ;
            case '%'    :   op2 = pop() ;
                            push(fmod(pop() , op2)) ;
                             break ;
            case SIN    :   if(errno == EDOM || errno == ERANGE)
                                printf("\n\t\t System Error!!") ;
                            else
                                push(sin(pop())) ;
                            break ;
            case COS    :   if(errno == EDOM || errno == ERANGE)
                                printf("\n\t\t System Error!!") ;
                            else
                                push(cos(pop())) ;
                            break ;
            case EXP    :   if(errno == EDOM || errno == ERANGE)
                                printf("\n\t\t System Error!!") ;
                            else    
                                push(exp(pop())) ;
                            break ;
            case POW    :   op2 = pop() ;
                            push(pow(pop() , op2)) ;
                            break ;
            default     :   printf("\nInvalid character...") ;
                            flag = 1 ;
                             break ;
        }
        if(flag == 1)  
            break ;
    }
                                //End of Polish_calc
}

int getop()                     // To get numerical operand , operator  and store the extra character into buffer
{
    char ch ;                   // stores character input will be used specially for storing extra read value in the buffer array
    int index_opr = -1 ;        // Current index value for Storing operand for operand array
    char Str[3] ;               // For Storing string to compare mathematical function

    if(top_buffer >= 0)
        return buffer[top_buffer--] ;
    while((ch = getchar()) == ' ' || ch == '\t') ;  // For removing blanks and tabs

    if(ch == 's' || ch == 'S' || ch == 'e' || ch == 'E' || ch == 'c' || ch == 'C' || ch == 'p' || ch == 'P')  
    {                           // Checking alphabets for using Mathematical Function and returning the result
        Str[0] = ch ;
            for(int iter = 1 ; iter < 3 ; iter++)
            {
                Str[iter] = getchar() ;
            }
        return Mathfunc(Str) ;
    }

    if( !isdigit(ch) && ch != '.' && ch != '-')
        return ch ;             // Not a Number
    if(ch == '-')               // Determining if '-' is an operator or part of negative numbers
    {
        buffer[++top_buffer] = ch ;
        if(isdigit(ch = getchar()) || ch != EOF)
        {
            operand[++index_opr] = buffer[top_buffer] ;
            buffer[top_buffer--] = '\0' ;
        }
        else
            return '-' ;
    }
    operand[++index_opr] = ch ;
    if(isdigit(ch))                                                         // Collecting integer part
            while(isdigit(ch = operand[++index_opr] = getchar()) ) ;
    if(ch == '.')                                                           // Collecting fractional part
            while(isdigit(ch = operand[++index_opr] = getchar()) ) ;
    operand[index_opr--] = '\0' ;                                           // To remove the extra read character
    if(ch != EOF && ch !=' ' && ch!='\t' && top_buffer < MAXNO)
        buffer[++top_buffer] = ch ;
    return NUMBER ;       
}

int Mathfunc(char ch[3])        // To calculate sin , cos and exp of given number
{   
    for(int index = 0 ; index < 3 ; index++)
        tolower(ch[index]) ;
    if(!strcmp( ch , "sin"))
        return SIN ;
    if(!strcmp( ch , "cos"))
        return COS ;
    if(!strcmp( ch , "exp"))
        return EXP ;
    if(!strcmp(ch , "pow"))
        return POW ;
    else    
    {
        flag = 1 ;
        return ch[0] ;
    }
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