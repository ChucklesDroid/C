#include <stdio.h>
#include <string.h>
#define MAXLINES 10

void Quicksort( char *line[] , int start , int end ) ;
int Partition( char *line[] , int start ,int end ) ;
void Swap(char *line[] , int index1 , int index2 ) ;
int main( int argc , char *argv[] )
{
    char *Lines[MAXLINES] ;
    Lines[0] = "Premier League is the best .\n" ;
    Lines[1] = "Manchester United \n" ;
    Lines[2] = "KOlkata \n" ;

    Quicksort( Lines , 0 , 2 ) ;
    for(int i = 0 ; i <3 ; i++ ) 
        printf("%s" , *(Lines + i) ) ;
    return 0 ;
}

void Quicksort( char *line[MAXLINES] , int start , int end )
{
    if( start >= end )
        return ;
    else {
        int Pindex = Partition( line , start , end ) ;
        Quicksort( line , start , Pindex - 1 ) ;
        Quicksort( line , Pindex + 1 , end ) ;
    }
}

int Partition( char *line[MAXLINES] , int start , int end )
{
    char *pivot = *( line + end ) ;  // Segmentation Fault shows up
    int Pindex = start ;
    for( int i = start ; i <= end ; i++ ) {
        if( strcmp( *(line + i) , pivot ) < 0 ) {
            Swap( line , i , Pindex ) ;
            Pindex++ ;
        }
    } 
    return --Pindex ;
}

void Swap( char *line[] , int index1 , int index2 )
{
    char *temp ;
    temp = *(line + index1) ;
    *(line + index1 ) = *( line + index2 ) ;
    *( line + index2 ) = temp ;
}