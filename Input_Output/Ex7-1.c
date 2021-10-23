// This program changes the case of the input text depending upon the name of the program

#include <stdio.h>
#include <ctype.h> 
#include <string.h>

int main( int argc , char *argv[] )
{
	char ch ;
		if( strcmp(*argv,"./upper") == 0 )
			while (( ch = getchar()) != EOF )
				printf("%c" ,toupper(ch) ) ;
		else
			while(( ch = getchar()) != EOF )
				printf("%c" ,tolower(ch) ) ;
	return 0 ;
}
