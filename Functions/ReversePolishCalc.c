#include<stdio.h>
#include<stdlib.h>          //For atof()
#include<ctype.h>
#define MAXOP 100           //Max size of operand or operator
#define NUMBER '0'          //signal that a number was found
#define MAXVAL 100          //maximum depth of val stack
#define BUFSIZE 100 

int getop(char []) ;
void push(double) ;
double pop(void) ;
int sp = 0 ;                //Next free Stack position
double val[MAXVAL] ;        //Value stack
int Getch(void) ;
void unGetch(int) ;
char buf[BUFSIZE] ;        //Buffer for ungetch 
int bufp = 0 ;              //Next free position in buf

/*Reverse Polish Calculator*/
main()
{
    int type ;
    double op2 ;
    char s[MAXOP] ;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER :
                    push(atof(s)) ;
                    break ;
        case '+' :
                    push(pop() + pop()) ;
                    break ;
        case '*' :
                    push(pop() + pop()) ;
                    break ;
        case '-' :
                    op2 = pop() ;
                    push(pop() - op2) ;
                    break ;        
        case '/': 
                    op2 = pop() ;
                    if(op2 != 0.0)
                        push(pop() / op2) ;
                    else
                        printf("error: zero divisor\n") ;
                    break ;
        case '\n':
                    printf("\t%.8g\n" , pop()) ;
                    break ;
        default:    
                    printf("error : unknown command %s\n" , s) ;
                    break ;
        }
    }
     return 0 ;
}

//push: push f onto value stack
void push(double f)
{
    if( sp < MAXVAL)
        val[sp++] = f ;
    else
        printf("error: stack full , can't push %g\n" , f) ;
}

//pop : pop and return top value from scratch
double pop(void)
{
    if(sp > 0)
        return val[--sp] ;
    else
        {
            printf("error: stack empty\n") ;
            return 0.0 ;
        }
}

//getop: get next operator or numeric operand
int getop(char s[])
{
    int i,c ;

    while((s[0] = c = Getch()) == ' ' || c == '\t' ) ;
    s[1] = '\0' ;
    if(!isdigit(c) && c != '.')
        return c ;          //not a number
    i = 0 ;
    if(isdigit(c))          //collect integer part
        while(isdigit(s[++i] = c = Getch())) ;
    if(c == '.')            //Collect Fraction part
        while(isdigit(s[++i] = c = Getch())) ;
    s[i] = '\0' ;
    if(c != EOF)
        unGetch(c) ;
    return NUMBER ; 
}

int Getch(void)             //get a (possibly pushed back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar() ;
}

void unGetch(int c)          //push character back on input
{
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters \n") ;
    else
        buf[bufp++] = c ;
}