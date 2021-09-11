#include <stdio.h>

int main( int argc , char *argv[] )
{
   char str[] = {'A' , 'M' , 'I' , 'T' , 'Y'} ;
   printf("%s", str) ;
   str[5] = '\0' ;
   printf("\n%s", str) ;
    return 0 ;
}