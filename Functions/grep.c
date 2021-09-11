/*By default grep is a UNIX program that that prints particular each line of
 *inputs that contain a special "pattern" or string of characters */

#include<stdio.h>
#include<string.h>
#define MAXLINE 1000

void grep (char String[] , char search[]) ;
int Getline(char String[]) ;
int main(void)
{
    char Line[MAXLINE] ;
    char Str_search[MAXLINE] ;
    printf("\n Enter String that needs to be searched for in the given line:-") ;
    scanf("%s", Str_search) ;
    scanf("%*c") ;
    while(Getline(Line) > 0)
    {
        grep(Line , Str_search) ;
    }
    return 0 ;
}

int Getline(char String[])
{
  char c_input ;
  int index = 0 ;  
  printf("\n Enter Line :-") ;
  while((c_input = getchar()) != '\n' && (index < MAXLINE - 1) )
  {
    String[index] = c_input ;
    index++ ;
  }
  if (c_input == '\n')
    String[index] = '\n' ;
  String[index + 1] = '\0' ;

  return index ;
}

void grep(char String[] , char search[])
{
  int flag ;
  for( int index = 0 ; String[index] != '\n' ; index++ )
  {
   flag = 0 ;
    if(String[index] == search[0]) ;
    {
      for(int index_j = 0 ; (index_j < strlen(search) - 1); index_j++)
      {
        if( String[index + index_j] == search[index_j])
          flag = 1 ;
        else
        {
          flag = 0 ;
          break ;
        } 
      }
    }
   if(flag == 1)
     printf("Line with reqd string is as follows :- %s" , String) ;
  }
}