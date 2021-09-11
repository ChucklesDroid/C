#include<stdio.h>
#include<string.h>

int strend( char *s , char *t )
{
    int len = strlen ( t ) ;
    s += len ;
    while( *s  ) {
        if( *s != *t++)
            return 0 ;
        s++ ;    
    }
    return 1 ;
}
 
main( int argc , char *argv[] )
{
    char s[] = "helloworld" ;
    char t[] = "world" ;
    int i = strend( s ,t ) ;
    printf("%d" , i ) ;
    return 0 ;
}