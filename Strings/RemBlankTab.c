//Write a program to remove trailing blanks and tabs from line or input and to delete currently blank lines
#include<stdio.h>
#include<string.h>
#define MAXLINE 1000

int Getline(char Line[MAXLINE]) ; //Takes input from the user and returns string length
int Remwhitespaces(char Line[MAXLINE]) ; //Removes trailing blanks and tabs and returns no. of blanks 
int main(void)
{
    char Line[MAXLINE] ;
    if(Getline(Line) > 0)
    {
        if(Remwhitespaces(Line) > 0)
            printf("Line :-%s" , Line) ;
    }
    return 0 ;
}

int Getline(char Line[MAXLINE])
{
    char c_input ;
    int index = 0; 
    while((c_input = getchar()) != '\n' && index < MAXLINE)
    {
        Line[index] = c_input ;
        index++ ;
    }
    if(c_input == '\n')
        Line[index] = '\n' ;
    Line[index + 1] = '\0' ;
    return index + 1;
}

int Remwhitespaces(char Line[MAXLINE])
{
    int str_len = strlen(Line) - 1 ;
    int index = str_len ;
        if( index > 0 && Line[index] == ' ' || Line[index] == '\t' || Line[index] == '\n' )
          index-- ;
        //Initialising new-line character and null character
        Line[index + 1] = '\n' ;
        Line[index + 2] = '\0' ;
    return (str_len - index) ;
}