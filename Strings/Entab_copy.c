/* Exercise 1-21. Write a program `entab` that replaces strings of
 * blanks by the minimum number of tabs and blanks to achieve the same
 * spacing. Use the same tab stops as for `detab`. When either a tab or
 * a single blank would suffice to reach a tab stop, which should be
 * given preference?
 */
#include<stdio.h>
#define TABVAL 8
#define MAXLINE 1000 

int Getline_entab(char Line[]) ;
int main(void)
{
    int line_len = 0;
    char Line[MAXLINE] ;
    while((line_len = Getline_entab(Line)) > 0)
        {
         printf("\n Altered Lines :-%s" , Line) ;
        }
    return 0 ;
}

int Getline_entab(char Line[])
{
    char c_input ;
    int index = 0 ;
    int noblanks = 0 ;
    while((c_input = getchar()) != '\n' && c_input != EOF && index < (MAXLINE - 1))
    {
        if(c_input == ' ')
        {
            if((index+1) % TABVAL == 0)
            {   
                Line[index] = '\t' ;
                noblanks = 0;   
            }
            else
            {
                noblanks++ ; 
            }                
        }
        else
        {
            for(; noblanks > 0 ; noblanks--)
            {
                Line[index - noblanks] = '_';
            }
            Line[index] = c_input ;
        }
        index++ ;
    }
        if(c_input == '\n')
        {
          Line[index] = '\n' ;
         }
          Line[index + 1] = '\0' ;
    return index ;
}