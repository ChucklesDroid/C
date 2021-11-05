//To change the page !!!
#include<stdio.h>
#include<string.h>

int main( void )
{	
	char Line[10] ;
	char eof = '.' ;
//	printf("Hello , world\fHello World") ;
	do{
		fgets(Line,10,stdin) ;
		printf("%s\n",Line) ;
	}while( strcasecmp(Line,&eof) != 0 ) ;
	return 0 ;
}
