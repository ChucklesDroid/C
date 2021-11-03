#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define PATTERNSIZE 100
#define LINENUM 1
#define INVERSION 2
#define LINEMAX 100

int options = 0 ;// Bit manipulation :- First bit value 1(int val = 1) represents Linenum , 2nd bit value 1(int val = 2) represents INVERSION(all lines except the ones with pattern will be printed)
void fpattern( FILE *, char *, char *) ; // Function compares the pattern from the filestream passed to it
int main( int argc , char* argv[])
{
	char pattern[PATTERNSIZE] ,c;

	while(--argc && *(*++argv) == '-' ){
		while( isalpha(c = *(++*argv)) ){
			switch(c){
				case 'n' : options |= LINENUM ;
					   break ;
				case 'x' : options |= INVERSION ;
					   break ;
				default  : fprintf(stderr,"Ivalid options passed \n Syntax:- grep [-nx]<filename ...>") ;
					   exit(1) ;
			}
		}
	}
	
	/* PATTERN */
	if( argc-- >= 1)
		strcpy(pattern,*argv) ;
	else {
		fprintf(stderr,"Pattern Missing....Program exiting!!") ;
		exit(1) ;
	}
	
	/* FILES */
	if(argc == 0)
		fpattern(stdin,pattern,NULL) ;
	else{
		while(argc--){
			FILE *fp ;
			if( (fp = fopen(*(++argv),"r")) != NULL )
				fpattern(fp,pattern,*argv) ;
			else
				fprintf(stderr,"\n%s : access denied",*argv) ;
		}
	}

	return 0;
}

void fpattern(FILE *fp , char pattern[PATTERNSIZE] , char filename[PATTERNSIZE] )
{
	unsigned Linenum  = 0 ;
	char Line[LINEMAX] ;
	char *match = NULL ;
		
	while( fgets(Line,LINEMAX,fp) != NULL ){
		match = strstr(Line , pattern ) ;
		if( !(options & INVERSION) && match != NULL )
			if( options & LINENUM )
				printf("%d : %s",++Linenum,Line) ;
			else
				printf("%s",Line) ;
		else if( (options & INVERSION) && match == NULL )
			if( options & LINENUM )
				printf("%d : %s", ++Linenum ,Line) ;
			else
				printf("%s", Line ) ;
		else
			continue ;
	}
}
