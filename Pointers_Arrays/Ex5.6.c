#include <stdio.h>
#include <string.h>

int Strindex( char *s , char *t ) ;
int main( int *argc , char *argv[] )
{
    char a[] = "abcdefabc" ;
    char b[] = "abc" ;
    int pos = Strindex( a , b ) ;
    printf("%d\n" , pos ) ;
    return 0 ;
}

int Strindex ( char *s , char *t )
{
    size_t pos = -1 ;
    size_t j ;
    for( size_t i = 0 ; i < strlen( s ) ; i++ )
    {
        if( *(s + i) == *t )
        {
            pos = i ;
            for( j = 0 ; j < strlen( t ) ; j++ ){
                if( *( s + j + i) != *( t + j) ){
                    pos = -1 ;
                    break ;
                }
            }
            if( pos != -1 && *(s + i + j + 1) == '\0' )
                return pos ;
        }
    }
    return pos ;
}