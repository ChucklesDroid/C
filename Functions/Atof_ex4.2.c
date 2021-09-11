// Extend atof to handle scientific notation of the form 123.45e-6 where a 
// floating no may be followed by e or E and an optionally signed exponent 

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
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
    int index_col = 0;                                                                   //index for string
    double val_dec = 0 ;                                                                 //integer part of double value to be returned
    double val_frac = 0 ;                                                                //Fractional part of double value to be returned
    int sign_val = 1;                                                                    //Sign of double value to be returned
    int exponent = 0 ;                                                                   //Exponent part of the value to be calculated
    int sign_exp = 1 ;                                                                   //Sign of exponent part 
            
    for(; isspace(String[index_col]) > 0; index_col++) ;                                 //checks for space
    sign_val = (String[index_col] == '-' ? -1:1 );                                       //assigns sign
    if(String[index_col] == '-' || String[index_col] == '+')                             //Current character is '-' then it increases index
        index_col++ ;         
    if(isalpha(String[index_col]))                                                       //Returns error if the character entered is an alphabet
        return -1 ;         
            
    for( ; String[index_col] != '.' && index_col < strlen(String) ;index_col++)          //Assigns the integer part
        val_dec = (val_dec * 10) + (String[index_col] - 48) ;                   
    
    if(String[index_col] == '.')                                                        //Assigns the fractional part       
    {
        index_col++ ;
        for(int index_dec = index_col ; String[index_col] != 'e' && String[index_col] != 'E' ; index_col++)
        {
           val_frac += (String[index_col] - 48) / pow(10 , index_col - index_dec + 1) ;     //Dummy variable index_dec created to calculate 10th power
        }
    }
    
    if(String[index_col] == 'e' || String[index_col] == 'E')                             //Checking for exponent values
    {         
        sign_exp = (String[++index_col] == '-' ? -1 : 1) ;         
        if(String[index_col] == '-' || String[index_col] == '+')                         //If value at current position is '-' or '+' it moves to the next character
            index_col++ ;         
        for(; index_col < strlen(String) ;index_col++ )         
        exponent = (exponent * 10) + (String[index_col] - 48) ;         
    }         
    if(exponent == 0)                                                                    //Adjusting the value of exponent so as to not cause error in the return statement
        exponent++ ;         
    if(sign_exp == 1)                                                                    //Adjusting value according to scientific notation  
        val_dec = sign_val * (val_frac + val_dec) * pow(10,exponent) ;
    else
        val_dec = sign_val * (val_frac + val_dec) / pow(10,exponent) ;
    return val_dec ;
}