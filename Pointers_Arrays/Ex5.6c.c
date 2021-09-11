#include <stdio.h>
#include <string.h>
#include <ctype.h>

int atoi( char *s ) ;
int main( int *argc , char *argv[] )
{
    char line[] = "19" ;
    int n = atoi ( line ) ;
    printf("%d" , n ) ;
    return 0 ;
}

int atoi ( char *s )
{
    int n = 0 ;
    while( isdigit( *s ) ) {
        n = n*10 + (*s - '0') ;
        s++ ;
    }
    return n ;
}