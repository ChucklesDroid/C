//Write a function that reverses the character string s. Use it to write a program
//that reverses its input a line at time
#include<stdio.h>
#include<string.h>
#define MAXLINE 1000

void ReverseString(char Line[]);
int Getline(char Line[]);
int main(void)
{
  char Line[MAXLINE] ;
  if(Getline(Line) > 0)
    ReverseString(Line) ;
  return 0 ;
}

int Getline(char Line[MAXLINE])
{
    char c_input ;
    int index = 0 ;
    while ((c_input = getchar()) != EOF && c_input != '\n' && index < MAXLINE-1)
    {
        Line[index] = c_input ;
        ++index ;
    }
    if(c_input == '\n')
     {   Line[index] = c_input ;
         Line[index + 1] = '\0' ; }
    return index + 1 ;
}

void ReverseString(char Line[MAXLINE])
{
    char c_input ;
    int index;
    int str_len = strlen(Line) - 2;
    for(index = 0 ; index < (str_len / 2) ; ++index)
    {
        c_input = Line[index] ;
        Line[index] = Line[str_len - index] ;
        Line[str_len - index] = c_input ;
    }
    printf("Reversed String is :-%s" , Line) ;
    
}