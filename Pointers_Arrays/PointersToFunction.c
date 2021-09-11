#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINES 10
#define MAXLEN 100
#define BUFFLEN 1000 

char Line_buffer[MAXLEN] ;
void display( char *Line_ptr[] , int size ) ;
int readlines( char *Line_ptr[] , int size ) ;
int getlines( char Line[] ) ;
void Quicksort( char *Line_ptr[] , int start , int end , int (*comp)( const char * , const char * )) ;
int Partition ( char *Line_ptr[] , int start , int end , int (*comp)( const char * , const char *)) ;
void swap( char *Line_ptr[] , int index1 , int index2 ) ;
int numcmp( char const *string1 , char const *string2 ) ;
void display( char *Line_ptr[] , int size ) ;
int main( int argc , char *argv[] )
{
    char *Line_ptr[MAXLINES] ;
    int nolines = 0 ;
    int numeric = 0 ;
    if( nolines = readlines( Line_ptr , MAXLINES )) {
        if( strcmp( *++argv , "-n") == 0 )
            numeric = 1 ;
        Quicksort( Line_ptr , 0 , argc - 1 , (int (*)( const char * , const char *))(numeric == 1 ? numcmp : strcmp) ) ;
    }
    display( Line_ptr , nolines ) ;
    return 0 ;
}

int readlines( char *Line_ptr[] , int size ) // Stores Lines in storage and also counts the no of lines
{
    char Line[ MAXLEN ] ;
    char *p = Line_buffer ;
    int nolines = 0 ; 
    int len = 0;
    while( (len = getlines( Line )) && p != NULL ){
        strcpy( p , Line ) ;
        Line_ptr[ nolines++ ] = p ;
        p += len ;
    }
    return nolines ;
}

int getlines( char Line[] ) // Takes one line from the user as input 
{
    char c ;
    int i = -1 ;
    while((c = getchar()) != '\0' && c != '\n' )
        Line[ ++i ] =  c;
    Line[ ++i ] = '\0' ;
    return i ;
}

void Quicksort( char *Line_ptr[] , int start , int end , int ( *comp )( const char * , const char *) )
{
    int Pindex ;
    if( start >= end )
        return ;
    else {
        Pindex = Partition( Line_ptr , start , end , comp ) ;
        Quicksort( Line_ptr , start , Pindex - 1 , comp ) ;
        Quicksort( Line_ptr , Pindex - 1 , end , comp ) ;
    }
}

int Partition( char *Line_ptr[] , int start , int end , int (*comp)( const char * , const char *))
{   
    int Pindex = 0 ;
    char *Pivot = Line_ptr[ end ] ;
        for( int i = start ; i <= end ; i++ ){
            if( ( *comp )( Line_ptr[i] , Pivot ) < 0 ) {
                swap( Line_ptr , i , Pindex ) ;
                Pindex++ ;
            }
        }
    return Pindex ;
}

void swap( char *Line_ptr[] , int index1 , int index2 )
{
    char *temp ;
    temp = Line_ptr[ index1 ] ;
    Line_ptr[ index1 ] = Line_ptr[ index2 ] ;
    Line_ptr[ index2 ] = temp ;
}

int numcmp( char const *string1 , char const *string2 )
{
    float c1 = atof( string1 ) ;
    float c2 = atof( string2 ) ;
    if( c1 < c2 )
        return -1 ;
    else if( c2 < c1 )
        return 1 ;
    else
        return 0 ;
}

void display( char *Line_ptr[] , int size )
{
    for( int i = 0; i < size ; i++ )
        printf("\n%d %s" , i + 1 , Line_ptr[i] ) ;
}