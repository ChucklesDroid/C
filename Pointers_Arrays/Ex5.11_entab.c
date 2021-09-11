#include<stdio.h>
#include<stdlib.h>
#define MAXLINE 10
#define TABVAL 8
#define YES 1
#define NO 0 

void settab( int argc , char *argv[] , char Line[MAXLINE]) ;
void entab( char Line[MAXLINE] ) ; 
int main( int argc , char *argv[] )
{
    char Line[MAXLINE] ;
    settab( argc , argv , Line ) ;
    entab( Line ) ;
    return 0 ;
}

void settab( int argc , char *argv[] , char Line[MAXLINE])
{
    int pos ;
    if ( argc == 1){
        for( pos = 1 ; pos < MAXLINE ; pos++ ) {
            if( pos % TABVAL == 0)
                Line[ pos ] = YES ;
            else
                Line[ pos ] = NO ;
        }
    }
    else {
        for( pos = 1 ; pos <= MAXLINE  ; pos++ )
            Line[ pos ] = NO ;
        while( --argc ){
            pos = atoi( *++argv ) ;
            if( pos > 0 && pos < MAXLINE )
                Line[ pos ] = YES ;
        }
    }
}

void entab( char Line[ MAXLINE ])
{
    char c ;
    int nb = 0 ;
    int nt = 0 ;
    for( int pos = 1 ; (c = getchar()) != '\0' ; pos++ ){
        if( c == ' ' || c == '\t' )
            if( Line[ pos ] == YES || c == '\t' ){
                nb = 0 ;
                nt++ ;
            }
            else
                nb++ ;
        else{
            for( ; nt > 0 ; nt-- )
                putchar( '\t' ) ;
            for( ; nb > 0 ; nb--)
                putchar( '_' ) ;
            putchar( c ) ;
            if( c == '\n'){
                pos = 1 ;
                nb = 0;
                nt = 0 ;
            }
        }
    }
}