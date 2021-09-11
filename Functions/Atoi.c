#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAXLINE 1000

long atoi(char String[]) ;
int main(int argc , char *argv[])
{
    long strn_val ;
    char strn[MAXLINE] ;
    printf("Enter String :-") ;
    scanf("%[^\n]%*c",strn) ;
        if((strn_val = atoi(strn)) > 0)
            printf("Converted string to int :- %ld" , strn_val) ;
        else
            printf("Cannot be converted !!") ;
    return 0 ;
}

long atoi(char String[])
{
    int strn_val = 0;
    int strn = strlen(String) - 1;
    int index_col = strn ; 
    for(; isspace(String[strn]) ; index_col--) ;
    for(; index_col >= 0 && String[index_col] >= 48 && String[index_col] <= 57; index_col--)
    {
       strn_val +=  ((String[index_col] - 48) * (int)pow(10,strn - index_col));
    }
    return strn_val ;
}