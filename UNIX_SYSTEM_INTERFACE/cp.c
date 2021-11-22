/*		-----------Copy of cp command in Linux-------------		*/
#include <stdio.h>
#include <unistd.h> // For read and write
#include <fcntl.h>  // For open and creat
#include <stdlib.h> // For exit()
#define BUFFSIZE 100

int buffer[BUFFSIZE] ;
void error( char *error_msg ) ;
int main( int argc, char *argv[] )
{
	int nb_read , nb_written , f1 ,f2 ;
	if( argc != 3 )
		error("usage :cp from to ...\n\tmissing files ...\n\tTerminating the program now !!") ;
	if( (f1 = open(argv[1] ,O_RDONLY,0755)) == -1 )
		error("error encountered while opening file\n\tTerminating the program !!") ;
	if( (f2 = creat(argv[2],0666)) == -1 )
		error("error encountered while creating file\n\t Terminating the program !!") ;
	while( (nb_read = read(f1,buffer,BUFFSIZE)) > 0)	
		if( (nb_written = write(f2,buffer,BUFFSIZE)) != BUFFSIZE )
			error("error encountered while copying file...\n\tOperation terminated \n\tFile not copied !!") ;
	return 0 ;
}

void error( char *error_msg )
{
	fprintf(stderr,"%s",error_msg) ;
	exit(1) ; //error encountered exiting the program now !!
}
