#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXSTRING 1000
#define BUFFMAX 10000
enum{ NAME ,
      PARENS,
      BRACKETS } ;
int PREVTOKEN = 0 ; // 1 means true and 0 means false
char BUFFER[BUFFMAX] ;
char out[MAXSTRING] ;
char name[MAXSTRING] ;
char datatype[MAXSTRING] ;
char token[MAXSTRING] ;
void parmdcl() ;
void dclspec() ;
void dirdcl() ;
void errordisp( char *string1 ) ;
void dcl( void ) ;
void ungetch( int c_buffer ) ;
int getch(void) ;
int gettoken() ;
int typequal() ;
int typespec() ;
int comp( char **string1 ,  char **string2 ) ;
int BUFFP = -1 ;
int tokentype ;
int main( int argc , char *argv[] )
{
    while( gettoken() != EOF ) {
        strcpy( datatype , token ) ;
        out[0] = '\0' ;
        dcl() ;
        printf("\n%s : %s %s" , name , out , datatype )  ;
    }
    return 0 ;
}

int gettoken()
{
    char c , *p = token ;
    if( PREVTOKEN )
        return tokentype ;
    else
        while( (c = getch()) == ' ' || c == '\t');


    if( isalpha(c) ){
        *p = c ;
        while( isalpha((*++p) = getch()) ) ;
        ungetch(*p) ;
        *p = '\0' ;
        return tokentype = NAME ;
    } else if( c == '('){
        //*p = c ;
        if( (c = getch()) == ')' ){
            //*p = '\0' ;
            strcpy( token , "()" ) ;
            return tokentype = PARENS ;
        } else{
            ungetch( c );
            //*p = '\0' ;
            return tokentype = '(' ; 
        }
    } else if( c == '[' ){
        *p = c ;
        while( ((*++p) = getch()) != ']' ) ;
        *++p = '\0' ;
        return tokentype = BRACKETS ;
    } else
        return tokentype = c ;

}

int getch( void )
{
    return (BUFFP >= 0) ? BUFFER[BUFFP--] : getchar() ;
}

void ungetch( int c_buffer )
{
    if( BUFFP >= BUFFMAX )
        errordisp("\nBuffer Full data overflow detected !!") ;
    else 
        BUFFER[++BUFFP] = c_buffer ;
}

void dcl()
{
    int np = 0 ;
    while( gettoken() == '*' )
        np++ ;
    dirdcl() ;
    while( np-- )
        strcat(out , " pointer to") ;
}

void dirdcl()
{
    if( tokentype == NAME )
        strcpy( name , token ) ;
    else if( tokentype == '('){
        dcl() ;
        if( tokentype != ')')
            errordisp("\nMIssing ) in (dcl) ") ;

    } else
        errordisp("\ndirdcl() reads only '(dcl)' or 'name'") ;


    while( gettoken() == PARENS || tokentype == BRACKETS || tokentype == '(' ){
        if( tokentype == PARENS )
            strcat(out , " function returning ") ;
        else if( tokentype == '('){
            strcat( out , " function expecting ") ;
            parmdcl() ;
        } else{
            strcat( out , " arrary") ;
            strcat( out , token );
            strcat( out , " of") ;
        }
    }
}

void parmdcl()
{
    do{
        dclspec() ;
        strcat( out , "," ) ;
    }while( tokentype != ')' && tokentype != EOF ) ;
    if( tokentype != ')' )
        errordisp("\nMissing ) at the end of parameter list ") ;
}

void errordisp( char *string1 )
{
    printf("\n%s" , string1 ) ;
}

void dclspec()
{
    char temp[MAXSTRING] ;
    gettoken() ;
    do {
        if( typequal() ){
            strcat( temp , token ) ;
            gettoken() ;
        } else if( typespec() ){
            strcat( temp , token ) ;
            gettoken() ;
        } else{
            PREVTOKEN = 1 ;
            dcl() ;
            gettoken() ;
        }
    } while( tokentype != ')' && tokentype != EOF && tokentype != ',') ;
    strcat( out , temp ) ;
}

int typequal()
{
    static char *qual[] ;
    qual[0] = (char *)malloc(4) ; qual[1] = (char *)malloc(8) ;
    *( qual ) = 'c'; ( *qual + 1 ) = 'h' ; ( *qual + 2 ) = 'a' ; ( *qual + 3 ) = 'r' ;
    *( qual + 1) = 'v' ; ( *( qual + 1) + 1 ) = 'o' ; ( *( qual + 1) + 2 ) = 'l' ; ( *( qual + 1) + 3 ) = 'a' ; ( *( qual + 1) + 4 ) = 't' ; ( *( qual + 1) + 5 ) = 'i' ; ( *( qual + 1) + 6 ) = 'l' ; ( *( qual + 1) + 7 ) = 'e' ; 
    char *pt = token ;
    if( bsearch( &pt , qual , sizeof(qual)/sizeof(char) , sizeof(char *) , comp) )
        return 1 ;
    else    
        return 0 ;
}

int typespec()
{
    static char *type[3] = { "char",
                      "float",
                      "int" } ;
    type[0] = (char *)malloc(4) ; type[1] = (char *)malloc(5) ; type[2] = (char *)malloc(3) ;
    
    if( bsearch( (void *)token , (void *)type , sizeof(type)/sizeof(char) , sizeof(char*) , comp) )
        return 1 ;
    else
        return 0 ;
}

int comp( char **string1 ,  char **string2 )
{
    //const char *key = string1 ;
    //const char *const *arg = string2 ;
    //printf("\n comp string1 : %s , string2 :%s ", string1 , string2 ) ;
    return strcmp( *string1 , *string2 ) ;
}