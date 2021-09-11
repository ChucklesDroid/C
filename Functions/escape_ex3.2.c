#include<stdio.h>
#define MAXLINE 1000
#define TABVAL 8

void escape(char s[MAXLINE] , char t[MAXLINE]) ;
int Getline(char Line[MAXLINE]) ;
int main(int argc , char *argv[])
{
    char String_s[MAXLINE] = " " ;
    char String_t[MAXLINE] = " " ;

    while (Getline(String_s) > 0)
    {
        escape(String_s , String_t) ;
        printf("String T is as follows :-%s" , String_t) ;
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
    return index ;
}

void escape(char s[MAXLINE] , char t[MAXLINE])
{
  int blanks = 0 ;
  int index_s = 0 ;
  int index_t = 0 ;
  char c_input = ' ' ;

  while(s[index_s] != '\0' && index_s < MAXLINE - 1)
  { 
      switch(s[index_s])
      {
          case '\t':{
                        if((index_s + 1) % TABVAL == 0)
                            blanks = 0 ;
                        else
                         blanks = TABVAL - ((index_s + 1) % TABVAL) ; 
                        
                        t[index_t] = '\\';
                        t[++index_t] = 't' ;
                        index_t++ ;
                        if(blanks != 0)
                            index_s += blanks ;
                        else
                            index_s++ ;
                        blanks = 0 ;
                    }
                        break ; 
          case '\n':{
                        t[index_t] = '\\' ;
                        t[++index_t] = 'n' ;
                        index_t++ ;
                        index_s++ ; 
                        blanks = 0 ;
                    }
                        break ;
          default :{
                        t[index_t] = s[index_s] ;
                        index_t++ ; index_s++ ;
                   }
                        break ;
      }
    if(s[index_s - 1] == '\n')
        break ;
  }  
}