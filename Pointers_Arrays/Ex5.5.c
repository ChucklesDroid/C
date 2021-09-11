#include<stdio.h>
#include<string.h>

char *Strncat( char *s , char *t , size_t n ) {
    char *bseadd = s ;
    int len = strlen( t ) ;
    size_t chrcatcnt = 0 ;
    while( *s ) s++ ;
    while( chrcatcnt != n ) {
        if( chrcatcnt <= len )  
            *s++ = *t++ ;
        else
            *s++ = '\0' ;
        chrcatcnt++ ;
    }
    *s = '\0' ;
    return bseadd ;
}

int Strncmp( char *s , char *t , int n ) {
    size_t chrcmpcnt = 0 ;
    while( chrcmpcnt != n ) {
        if( *s != *t )
            return (*s - *t) ;
        s++ ; t++ ; chrcmpcnt ++;
        }
    return 0 ;
}

char *Strncpy( char *s , char *t , size_t n ) {
    char *bseadd = s ;
    size_t chrcpycnt = 0 ;
    while(  chrcpycnt != n ) {
        *s++ = *t++ ;
        chrcpycnt++ ;
    }
    *s = '\0' ;
    return bseadd ;
}

int main( int argc , char *argv[] )
{
    char s[15] = "Hello" ;
    char t[] ="Hrlld" ;
    int i ;
    char u[15] ;
    //Strncat( s , t , 3 ) ;
    //i = Strncmp( s , t , 3 ) ;
    Strncpy(u , t , 3 ) ;
    printf("%s" , u ) ;
    //printf("%s" , s ) ; 
    //printf("%d" , i ) ;
    return 0 ;
}