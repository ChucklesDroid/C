#include<stdio.h>

void iota( int num ) ;
int main(int argc , char *argv[])
{
    int num ;
    printf("\nEnter an integer := ") ;
    scanf("%d" , &num) ;
    iota(num) ;
    return 0 ;
}

void iota( int num )
{
    char ch[10] ;
    int i = -1 ;
    while( num != 0 )
    {
        ch[ ++i ] = (num % 10) + 48 ;
        num = num / 10 ;
    }
    ch[ i + 1 ] = '\0' ;
    printf("\nThe reverse no is %s" , ch) ;
    for( int j = 0 ; j < i / 2 ; j++)
    {
        char temp ;
        temp = ch[ j ] ;
        ch[ j ] = ch[ i - j ] ;
        ch[ i - j ] = temp ;
    }
    printf("\nThe exact no is %s" , ch) ;
}