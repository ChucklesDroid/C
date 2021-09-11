//Write a program that reads a set of text lines and prints the longest
#include<stdio.h>
#define MAXLEN 1000

int Getline(char line[] ) //input line from user and returns line length
{ 
    int index_count = 0;
    char c_input;
    printf("\n Enter a new line :- ") ;
    while((c_input = getchar()) != '\n' && (index_count < MAXLEN - 1))
    {
        line[index_count] = c_input ;
        index_count++ ;
    }
    if( c_input == '\n')
    line[index_count] = '\n';
    //End of string indicator 
    line[index_count + 1] = '\0' ;
    return index_count ;
}


void Line_copy( char from[] , char to[]) //Copy current_line to maximum length line  
{
    for( int index_count = 0 ; index_count < MAXLEN && from[index_count] != NULL ; index_count++)
        to[index_count] = from[index_count] ;
}


int main(void)
{
    int current_len ;
    int max_len = 0;
    char Current_line[MAXLEN] ;
    char Largest_line[MAXLEN] ;

    while((current_len = Getline(Current_line)) > 0)
    {
        if(current_len > max_len)
        {
            max_len = current_len ;
            Line_copy(Current_line , Largest_line) ;
        }
    }
    
    if(current_len == 0)
    { printf("\nNo New line entered!!!!\n") ;}
    printf("Maximum Length of the line is %d \nMaximum Length Line is %s \n" , max_len , Largest_line) ;
    return 0 ;
}