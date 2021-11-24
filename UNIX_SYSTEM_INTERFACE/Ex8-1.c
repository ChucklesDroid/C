/*				-----------------Copy of cat command----------------*/
#include <stdio.h>  // For vfprintf
#include <unistd.h> // For write,close and read
#include <fcntl.h>  // For macro O_RDONLY and open()
#include <stdarg.h> // For variable argument list in functions
#include <stdlib.h> // For exit function
#define BUFFSIZ 100

void cat( ssize_t fd ) ; // Concatenates input from the appropriate file descriptor and publishes the output on the stdout
void error( char *fmt ,... ) ; // Publishes error on stderr
int main( int argc , char *argv[] )
{
	ssize_t fd ;
	if( argc < 1 )
		cat(0) ;
	else
		while( (fd=open(*++argv,O_RDONLY,0)) > 0 && --argc > 0)
			cat(fd) ;
	if( fd == -1 && argc < 1){
		close(fd) ;
		error("%s: error opening file ...\n\tAborting the operation",argv[0]) ;
	}
	return 0 ;
}

void cat( ssize_t fd )
{	
	char buffer[BUFFSIZ] ;
	int nb_read ;
	while( (nb_read=read(fd,buffer,BUFFSIZ)) > 0 ){
		//buffer[nb_read] = '\0' ;
		if( write(1,buffer,nb_read) != nb_read )
			error("error encountered ...\n\tTerminating the program") ;
	}
	close(fd) ;
}

void error( char *fmt , ... )
{
	va_list ap ;
	va_start(ap,fmt) ;
	vfprintf(stderr,fmt,ap) ;	
	va_end(ap) ;
	exit(1) ;
}
