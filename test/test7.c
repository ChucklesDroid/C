#include<stdio.h>
#include<ctype.h>

void add( int n1 , int n2 ) ;
void PtrFunc( void (*func)(int , int) , int n1 , int n2 ) ;
void Ptr2( void (*func)( int , int ) , int n1 , int n2 ) ;
int main( void )
{
    PtrFunc( (void (*)( int , int ))add , 1 , 2 ) ;
    return 0 ;
}

void add( int n1 , int n2 )
{
    printf("%d" , n1 + n2 ) ;
}

void PtrFunc( void (*func)(int , int) , int n1 , int n2 )
{
    Ptr2(func , n1 , n2 ) ;
}

void Ptr2( void (*func)(int , int) , int n1 , int n2 )
{
    (*func)( n1 , n2 ) ;
}
