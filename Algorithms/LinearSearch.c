/* Linear Search checks each value sequentially using a simple loop
   It does not require a sorted data .*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STUDSIZE 2

struct Student{
    char studName[20] ;
    int studRollNo ;
    int studMarks ;
} S[5];

void input( void ) ;
int choice( void ) ;
int names( void ) ;
int rollno( void ) ;
void display( int pos ) ;
int main( int argc , char *argv[] )
{
    int chce ;
        input() ;
    while( chce != 2) {
        display( (choice() == 1) ? names() : rollno() ) ;
        printf("\nDo you want to continue ? 1.Yes 2.No\n") ;
        scanf("%d", &chce ) ;
    }
    return 0 ;
}

void input( void )
{
    printf("\nEnter information about the %d students" , STUDSIZE ) ;
        for( int i =0 ; i < STUDSIZE ; i++ ){
            printf("\nEnter Name :-") ;
            scanf("%[^\n]%*c" , S[i].studName ) ; 
            printf("Enter Roll No :-") ;
            scanf("%d" , &S[i].studRollNo ) ;
            printf("Enter Marks of the student :-") ;
            scanf("%d%*c" , &S[i].studMarks ) ;
        }
}

int choice( void )
{   
    system("clear") ;
    int choices ;
    printf("\n1.Search using student Name .") ;
    printf("\n2.Search using student Rollno .\n") ;
    scanf("%d" , &choices ) ;
    return choices ;
}

int names( void )
{
    char name[20] ;
    int flag = 0 , i ;
    printf("\nEnter name to be searched for :-") ;
    scanf("%*c%[^\n]%*c" , name ) ;
    for( i = 0 ; i < STUDSIZE ; i++ )
        if( strcmp( name , S[i].studName ) == 0 ){
            flag = 1 ;
            break ;
        }
    if( flag == 1 )
        return i ;
    else    
        return -1 ;
}

int rollno( void )
{
    int flag = 0 , i , num ;
    printf("\nEnter rollno to be searched for :-") ;
    scanf("%d" , &num ) ;
    for( i = 0 ; i < STUDSIZE ; i++ )
        if( num == S[i].studRollNo ){
            flag = 1 ;
            break ;
        }
    if( flag == 1 )
        return i ;
    else
        return -1 ;
}

void display( int pos )
{
    if( pos == -1 ){
        printf("\nError detected !!!....No value found") ;
        return ;
    }
    else {
        system("clear") ;
        printf("\nValue detected at position = %d" , pos + 1 ) ;
        printf("\nName :- %s" , S[pos].studName ) ;
        printf("\nRollno :- %d" , S[pos].studRollNo ) ;
        printf("\nMarks :- %d" , S[pos].studMarks ) ;
    }
}