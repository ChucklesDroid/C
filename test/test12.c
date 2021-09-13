#include<stdio.h>

int main( int argc , char *argv[] )
{
    char *s[]={ "char" , "int" } ;
    printf("%s : %p" , *s[0] , s[0] ) ;
    printf("%s : %p" , *s[1] , s[1] ) ;
    return 0 ;
}