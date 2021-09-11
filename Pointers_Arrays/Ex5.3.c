#include<stdio.h>
#include<string.h>

char *Strcat(char *a , char *b)
{
    while( *( ++a ) ) ; 
    while( ( *a++ = *b++ ) );
    return a ;
    }
int main(int argc , char *argv[])
{
    char s[15] = "Hello" ;
    char t[] = "World" ;
    Strcat( s, t) ;
    printf("s=%s\n" , s) ;
    printf("t=%s\n", t) ;
    return 0 ;
}