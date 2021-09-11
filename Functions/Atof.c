#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXLINE 1000

double Atof(char String[MAXLINE]) ;
int main(int argc , char *argv[])
{
    char String[MAXLINE] ;
    double val ;
    printf("Enter the desired string :-") ;
    scanf("%[^\n]%*c",String) ;
    if((val = Atof(String)) > 0 )
        printf("Converted String to double :- %lf",val) ;
    else
        printf("\nError!!") ;
    return 0 ;
}

double Atof(char String[])
{
    int index_col = 0;
    double val_dec = 0 ;
    double val_frac = 0 ;
    int sign_val = 1;
    for(; isspace(String[index_col]) > 0; index_col++) ;                        //checks for space
    sign_val = (String[index_col] == '-' ? -1:1 );                              //assigns sign
    if(String[index_col] == ' ')                                                //Current character is '-' then it increases index
        index_col++ ;
    if(isalpha(String[index_col]))                                              //Returns error if the character entered is an alphabet
        return -1 ;
    for( ; String[index_col] != '.' && index_col < strlen(String) ;index_col++) //Assigns the integer part
        val_dec = (val_dec * 10) + (String[index_col] - 48) ;                   
    if(String[index_col] == '.')                                                //Assigns the fractional part       
    {
        index_col++ ;
        for(int index_dec = strlen(String) - 1; index_dec >= index_col ; index_dec--)
        {
           val_frac = (val_frac + (String[index_dec] - 48 )) / 10 ; 
        }
    }
    return (sign_val*(val_frac+val_dec)) ;
}