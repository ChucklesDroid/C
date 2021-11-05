/* 				Postfix Calculator of Chapter 4 using scanf 	*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define OPMAX 100
#define NUM 0
#define STACKMAX 100

float stack[STACKMAX] ; // Stores operands in this array , utilisation as stack
int top = -1 ;	// Determines the top of Stack
int getop( char *) ;
float pop() ;
void push( float c ) ;
int main( int argc, char *argv[] )
{
	char oper[OPMAX] ;
	int ch ;
	float op2 ;
	while((ch = getop(oper) ) != EOF ){
		switch(ch){
			case NUM : push(atof(oper)) ;
				   break ;
			case '+' : push(pop() + pop()) ;
				   break ;
			case '*' : push(pop() * pop()) ;
				   break ;
			case '/' : op2 = pop() ;
				   push(pop() - op2) ;
				   break ;
			case '-' : op2 = pop() ;
				   push(pop() - op2) ;
				   break ;
			default :  if( ch == '\n')
							continue ;
					   else
				 			printf("\nInvalid Operation!!") ;
				   	   break ;
		}
	}
	printf("\n%f\n" , stack[0]) ;
	return 0 ;
}

/* Gets operator or operand from the input stream */
int getop( char s[OPMAX] )
{	
	int c ,rc ;
	float f ;
	while((rc = scanf("%c", &c)) != EOF)	/* Skips blanks and tab spaces */
		if ( (s[0] = c) != ' ' && c != '\t' )
			break ;
	
	s[1] = '\0' ;
	if( rc == EOF )
		return EOF ;	/* If EOF encountere */
	if( !isdigit(s[0]) && s[0] != '.' ) /* Not a digit */
		return s[0] ;
	ungetc( c , stdin ); 	/* pushes character back to the input stream */
	scanf("%f",&f) ; 		
	sprintf(s,"%f",f) ;		/* stores the float value in s */
	return NUM ;			/* Returns number */
	
}

/* Push operator onto the stack */
void push( float f )
{
	if( top < OPMAX )
		stack[++top] = f ;
	else
		printf("Stack overflow") ;
}

/* Returns the operator from the stack */
float pop()
{
	if( top >= 0 )
		return stack[top--] ;
	else
		printf("Stack underflow") ;
}

