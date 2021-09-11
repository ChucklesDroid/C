#include<stdio.h>
#include<string.h>
#include<ctype.h>
enum { NAME ,               
       PARENS ,
       BRACKETS };
#define MAXLEN 100         // Max length of token read
#define BUFFERLEN 1000     // Max length of BUFFER

char BUFFER[ BUFFERLEN ] ; // Stores the overread value 
int BUFFP = -1 ;           // Exact position of cursor in BUFFER
int tokentype ;            // Stores the type token read by gettoken from stdinput
char token[MAXLEN] ;       // Stores the token read by gettoken from stdinput
char out[MAXLEN] ;         // Stores the output string 
char name[MAXLEN] ;        // Stores the name of variable 
char datatype[MAXLEN] ;    // Stores the name of datatype like char , int 

// collects input from stdinput or BUFFER depending on the value of BUFFP 
// returns it to the caller
int getch() 
{
    return ( BUFFP >= 0 ) ? BUFFER[ BUFFP-- ] : getchar() ;
}

// stores overread character from input into the BUFFER
// argument is of type int which is the value to be stored in the buffer
void ungetch( int c ) 
{
    if( BUFFP < BUFFERLEN && c != ' ' && c != '\t' )
        BUFFER[ ++BUFFP ] = c ;
    else if( BUFFP > BUFFERLEN )
        printf("\n Bufferoverflow !!") ;
}

// It collects input from the stdinput
// returns integer value of the tokentype 
int gettoken() 
{
    char c ; // Stores character returned by getch()
    char *p = token ; // Pointer to array token 
    while( (c = getch())  == ' ' || c == '\t' ) ; // discard whitespace characters from retrieved from inputstream

    if( c == '('){
        if( (c = getch()) == ')' ){
            strcpy( token , "()" ) ;
            return tokentype = PARENS ; 
        }
        else{
            ungetch(c) ;
            return tokentype = '(' ;
        }
    } 

    else if( c == '[' ){
        for( *p++ = c ; (*p = getch()) != ']' ; p++ ) ;
        *(++p) = '\0' ;
        return tokentype = BRACKETS ;
    }

    else if( isalpha(c) ){
        for( *p++ = c ; isalnum( *p = getch() ) ; p++);
        ungetch( *p ) ;
        *p = '\0' ;
        return tokentype = NAME ;
    }

    else
        return tokentype = c ;
}

// Recursive descent parser uses dcl() and dirdcl() to parse tokens from stdinput
// dcl() parses dcl from stdinput and calls dirdcl() to parse dirdcl()
void dirdcl() ;
void dcl() 
{
    int np = 0 ; // no of pointers stored in the variable
    while( gettoken() == '*')
        np++ ;
    dirdcl() ;
    while( np-- )
        strcat( out , " pointer to") ;
}

// Parses dirdcl() from the input according to grammar
void dirdcl() 
{
    int type ;
    if( tokentype == NAME )
        strcpy( name , token ) ;

    if( tokentype == '('){
        dcl() ;
        if( tokentype != ')' )
            printf("\n Syntax Error : Missing ')' ") ;
    }

    while( (type = gettoken()) == PARENS || type == BRACKETS ) {
        if( type == PARENS )
            strcat( out , "function returning") ;
        else if( type == BRACKETS ){
            strcat( out , " array") ;
            strcat( out , token ) ;
            strcat( out , " of" ) ;
        }
    }
}

int main( int argc , char *argv[] )
{
    while( gettoken() != EOF ){
        strcpy( datatype , token ) ;
        out[0] = '\0' ; 
        dcl() ;

        printf("%s : %s %s" , name , out , datatype ) ;
        scanf("%*c") ;
    }
    return 0 ;
}
