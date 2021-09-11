#include <stdio.h>
#include <math.h>

int main(int argc , char *argv[])
{
   int a[95] ;
   int modulo ;
   long double sum = 1.0 ;
   for(int i = 0 ; i < 95 ; i++)
    scanf("%d" , &a[i]) ;
   for(int i = 0 ; i < 95 ; i++)
    sum *= a[i] ;
    modulo = (int)(fmod(sum , 1234567.0)) ;
    printf("\n%d" , modulo) ;
    return 0 ;
}