#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXENTRIES 3

struct TelephoneDirectory{
    char Name[25] ;
    long Phone ;
} T[10] ;

void Quicksort( int start , int end ) ;
int Partition( int start , int end ) ;
void input( void ) ;
void Swap( int index1 , int index2 ) ;
int BinarySearch( void ) ;
void display( int pos ) ;
int main( int argc , char *argv[] )
{
    input() ;
    Quicksort( 0 , MAXENTRIES - 1) ;
    display( BinarySearch() ) ;
    return 0 ;
}

void input( void )
{
    printf("\nEnter %d entries in the Telephone Directory" , MAXENTRIES ) ;
    for( int i = 0 ; i < MAXENTRIES ; i++ ){
        printf("\nEnter Name :- ") ;
        scanf("%[^\n]%*c" , T[i].Name ) ;
        printf("Enter Phone No :=") ;
        scanf("%d%*c" , &T[i].Phone ) ;
    }
}

void Quicksort( int start , int end ) 
{
    if( start >= end )
        return ;
    else {
        int Pindex ;
        Pindex = Partition( start , end ) ;
        Quicksort( start , Pindex - 1 ) ;
        Quicksort( Pindex + 1 , end ) ;
    }
}

int Partition( int start , int end )
{
    char Pivot[25] ;
    strcpy(Pivot , T[end].Name ) ;
    int Pindex = start ; // T[end].Name is taken as pivot 
    int val ;
    for( int i = start; i <= end ; i++ ){
        if( val = (strcmp( T[i].Name , Pivot ) ) <= 0 ) {
            Swap( i , Pindex ) ;
            Pindex++ ;
        }
    }
    return Pindex - 1;
}

void Swap( int index1 , int index2 )
{
    struct TelephoneDirectory temp ;
    temp = T[index1];
    T[index1] = T[index2] ;
    T[index2] = temp ;
}

void display( int pos ) 
{
    system("clear") ;
        if( pos < 0 )
            printf("\n Name does not exist !!") ;
        else{
            printf("\nName :- %s" , T[pos].Name ) ;
            printf("\tPhone No :- %d\n" , T[pos].Phone ) ;
    }
}

int BinarySearch( void )
{
    int start = 1 ,  end = MAXENTRIES , mid ;
    char name[25] ;
    printf("\nEnter Name to be searched :-") ;
    scanf("%[^\n]%*c" , name ) ;
    while( start <= end ){
        mid = ( start + end )/2 ;
        if( strcmp( T[mid - 1 ].Name , name ) == 0 )
            return mid - 1 ;
        else if( strcmp( name ,T[mid - 1].Name ) < 0 )
            end = mid - 1 ;
        else if( strcmp( name ,T[mid - 1].Name ) > 0 )
            start = mid + 1 ;
    }
    return -1 ;
}
