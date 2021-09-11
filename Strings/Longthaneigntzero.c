//Write a program to print all input lines that are longer than 80 characters
#include <stdio.h>
#define MAXLINE 1000

int Getlen( char len[]) ;
int main(void)
{
  char Lines[MAXLINE] ;
   //Inputing Lines and Printing them
  while(Getlen(Lines) > 80)
  {
    printf("%s\n" , Lines) ;
  }
  return 0;
}

int Getlen(char Len[]) //Inputing string and returning length of Lines
{
    char c_input ;
    int index = 0 ;
    printf("Enter Line ( > 80 characters) : -- ") ;
    for(index ; (c_input = getchar()) != EOF && (c_input != '\n') && index < MAXLINE - 1 ; index++)
        Len[index] = c_input ;
    
    if(c_input == '\n')
        Len[index] = '\n' ;
    Len[index + 1] = '\0' ;
    if(index < 80)
        printf("\n Entered line is not 80 characters long\n") ;
    return index ;
}