#include<stdio.h>
#include<ctype.h>
#define MAXLEN 8 

int main( int argc , char *argv[] )
{
	char str[] = "all \a about \t programming tutorials \n point.";
	char c ;
	int pos = 0 , i = 0;
		while( (c = str[i++]) != '.' ) {
			if( iscntrl(c) > 0){
				if( c == '\n')
					pos = 0 ;
			}
			else {
				if( pos <= MAXLEN )
					putchar(c) ;
				else{
					pos = 0 ;
					printf("\n %c",c ) ;
				}
			}
		}
	return 0 ;
}
