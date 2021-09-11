#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLINES 10
#define BUFFERMAX 1000
#define MAXLEN 100
#define NPRINT 1

char *Line_ptr[ MAXLINES ] ;
char Line_buffer[ BUFFERMAX ] ;
int readlines( char *Line_ptr[] ) ;
int Getline( char Line[] , int size ) ;
int main( int argc , char *argv[] )
{
    int nolines = 0;
    int nprint = NPRINT ;
    if( nolines = readlines( Line_ptr)) {
        if( argc > 1 && *(*++argv) == '-')
            nprint = (int)*(++(*argv)) - '0';
        if( nprint > nolines )
            nprint = nolines ;
        for( int i = 0 ; i < nprint ; i++ )
            printf("\n%d %s" , i + 1 , *( Line_ptr + i)) ;
    }
    else
        printf("\nError Stack Empty!!!!....") ;
    return 0 ;
}

int readlines( char *Line_ptr[] )
{
    int nlines = 0 ;
    int len ;
    char Line[ MAXLEN ] ;
    char *p = Line_buffer ;
    while( (len = Getline( Line , MAXLEN )) > 0 && p != NULL ) {
        strcpy( p , Line ) ;
        Line_ptr[ nlines++ ] = p ;
        p += (len + 1) ;
    }
    return nlines ;
}

int Getline( char Line[] , int size )
{
    int i = -1 ;
    char c ;
    while( (c = getchar()) != '\n' && c != '\0' && i < size-1 )
        Line[ ++i ] = c;
    Line[ ++i ] = '\0' ;
    return i ; 
}