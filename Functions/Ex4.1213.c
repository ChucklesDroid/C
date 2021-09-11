#include <stdio.h>
#include <string.h>
#define SIZE 10
char num[SIZE] ;

void iota( int num ) ;
void reverse() ;
int main(int argc , char *argv[])
{
    int n = 9089 ;
    iota( n ) ;
    printf("%s ",num ) ;  
    return 0 ;
}

void iota( int n ) 
{
    static int i = 0 ;
    if((( n / 10 ) == 0) && (( n % 10 ) == 0))
    {
        num[i] = '\0' ;
        reverse() ;
        return ;
    }
    num[ i++ ] = (char)(n % 10 + '0') ;
    iota(n/10) ;
}

void reverse()
{
    char temp ;
    int len = strlen( num ) - 1 ;
    static int i = 0 ;
        if( i > len/2 )
         return ;
        temp = num[ i ] ;
    num[ i ] = num[ len-i ] ;
    num[ len - i ] = temp ;
        i++ ;
    reverse() ; 
        
}   