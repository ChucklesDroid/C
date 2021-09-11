/* Write a program to "fold" long input lines into two or more shorter lines after 
 * the last non blank character that occurs before the n-th column input, Make sure 
 * your does something intelligent with very long lines and if there are no blanks
 * or tabs before the specified column.
 */
#include<stdio.h>
#define MAXLINE 1000
#define TABVAL 8
#define MAXCOL 10

void formattedprint(char Strings[MAXLINE]) ;
int Getline(char Strings[MAXLINE]) ;
int main(void)
{
    char c_input ;
    char Strings[MAXLINE] ;
    while(Getline(Strings) > 0)
    {
        formattedprint(Strings) ;
    } 
    return 0 ;
}

int Getline(char Strings[MAXLINE])
{
    int index = 0 ;
    char c_input ;
    while((c_input = getchar()) != '\n' && c_input <= MAXLINE && c_input != EOF && index < (MAXLINE - 1))
    {
        Strings[index] = c_input ;
        index++ ;
    }
    if(c_input == '\n')
        Strings[index] = c_input ;
    Strings[index + 1] = '\0' ;
    return index ;
}

void formattedprint(char Strings[MAXLINE])
{
    int index = 0 ;
    int pos = 1;
    int noblanks = 0 ;
    for(; Strings[index] != '\0' ; index++)
    {
        if( Strings[index] == '\t')
        {
            noblanks = TABVAL -((index)% TABVAL) ;
            for(; noblanks > 0 ; noblanks--)
            {
                if(pos > MAXCOL)
                {
                 printf("\n") ;
                 pos = 1 ;
                 printf("_") ;
                }
                else
                {
                    printf("_") ;
                    pos++ ;
                }
            }
        }
        else
        {
            printf("%c", Strings[index]) ;
            pos++ ;
        }
        if(pos == MAXCOL)
        {
            printf("\n") ;
            pos = 0 ;
        }
    }
}