#include <stdio.h>

void filecopy( FILE * , FILE *) ;

int main( int argc , char *argv[] )
{
	FILE *fp ;

	if(argc == 1)
		filecopy(stdin,stdout) ;
	while( --argc ){
		if( (fp=fopen(*(++argv),"r")) != NULL )
			filecopy( fp , stdout ) ;
		else
			printf("\nFile does not exist") ;
	}
	fclose(fp) ;
	return 0 ;
}

void filecopy( FILE *ifp , FILE *ofp )
{
	int c ;
	while( (c=getc(ifp)) != EOF )
		putc(c,ofp) ;
}
