#include<stdio.h>
#define NUMERIC   1
#define DECR      2 /* sorts in decreasing order */

static char option = 0;
int main( int argc , char *argv[] )
{
    printf("%d",option |= NUMERIC );
    printf("\n%d",option ) ;
    printf("\n%d" ,option |= DECR );
    printf("\n%d",option ) ;
    printf("\n%d",option & NUMERIC) ;
    printf("\n%c" , (*++argv)[0] ) ;
    printf("\n%c" , *(++argv)[0] ) ;
    return 0 ;
}