#include <stdio.h>
#include <stddef.h>
#define SIZE 100 

char Line[ SIZE ] ;
ptrdiff_t Getline( void ) ;
int main( int *argc , char *argv[] )
{
    Getline() ;
    printf("%s" , Line) ;
    return 0 ;
}
   
ptrdiff_t Getline ( void )
{
    char *s = Line ;
    while( ( *(s++) = getchar() ) != '\n' ) ;
    s = '\0' ;
    return ( s - Line ) ;
}
