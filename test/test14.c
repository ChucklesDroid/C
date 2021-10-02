#include<stdio.h>
#include<stdlib.h>
int main( void )
{
    char *print( char *p){
        p = (char *)malloc( sizeof(char) ) ;
        *p = getchar();
        return p ;
    }
    char *c = NULL ;
    c = print(c) ;
    printf("%c", *c) ;
    return 0 ;
}