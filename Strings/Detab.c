//Write a program detab that replaces tabs in input with the proper no of blanks
//to space to the next tab stop . Assume a fixed set of tab stops say every n 
//columns. Should n be a variable or a symbolic parameter?
//Solution :-- 
//TABVAL is a symbolic constant. Later on, in Chapter 5 , you will learn
//how to pass arguments to the main program and you may want to allow the user
//to set the number of columns between tab stops. Then you may want to change
//TABVAL into a variable.
//The program Detab is extended in Exercises 5-11 and 5-12.
#include<stdio.h>
#define MAXLINE 1000
#define TABVAL 8

int Getline_Detab(char Line[]) ;
int main(void)
{
    int line_len = 0;
    char c_input ;
    char Line[MAXLINE] ;
    while((line_len = Getline_Detab(Line)) > 0)
    {    
            printf("\nline is :-%s" , Line) ;        
    }
    return 0 ;
}

int Getline_Detab(char Line[])
{
    char c_input ;
    int index = 0 ;
    int noblank = 0 ;
    while((c_input = getchar()) != '\n' && index < MAXLINE - 1 )
    {
        if(c_input == '\t')
        {   
            int index_temp = index ;
            noblank = TABVAL - ((index + 1) % TABVAL) ;
            while(index != (index_temp + noblank))
            {
                Line[index] = '_' ;
                ++index ; 
            }
            Line[index] = '_' ;
            ++index ;
        }
        else
        {
            Line[index] = c_input ;
            index++ ;
        }
    }
    if(c_input == '\n')
      Line[index] = '\n' ;
    Line[index + 1] = '\0' ;
    return index ;
}

