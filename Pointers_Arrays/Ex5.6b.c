#include <stdio.h>
#include <string.h>
#include <stddef.h>
#define SIZE 5 

void reverse ( char s[] ) ;
void iota( char *s , int n ) ;
int main( int *argc , char *argv[] )
{
    char line[SIZE] ;
    int n = 3411 ;
    iota( line , n ) ;
    printf("%s" , line) ;
    return 0 ;
}
   
void reverse ( char *s )
{
    char temp ;
    size_t len = strlen( s ) ;
    for( size_t i = 0 ; i < len/2 ; i++ ){
        temp = *( s + i );
        *( s + i ) = *( s + len - 1 - i ) ;
        *( s + len - 1 - i ) = temp ;
    }
}

void iota( char *s , int n )
{
    char *bseadd = s ;
    *s++ = ( n % 10 ) + '0' ;
    while( n = n / 10 ) {
     *s++ = (n % 10) + '0' ;
    }
    printf("%s\n" , bseadd ) ;
    reverse( bseadd ) ;
}