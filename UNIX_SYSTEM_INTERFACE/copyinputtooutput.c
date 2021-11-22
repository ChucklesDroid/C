/*	This program reads input from file descriptor 0(stdin) and writes it into file descriptor 1(stdout) */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFSIZE 100

char buff[BUFFSIZE] ;
int main( int argc ,char *argv[] )
{
	int n ;
	while( n=read(0,buff,BUFFSIZE) >0 ){ // value of n may not be accurate
		write(1,buff,sizeof(buff)) ;
	}
	return 0;
}

/*	unbuffered version  */
/*int getchar( void )
{
	char buff;
	return (read(0,&buff,1) > 0 ? buff : EOF) ; 
}
*/
/*	to read string	*/


