#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LNCNT 20

size_t WRDCNT=100 ;
void footer() ;
void Pgprint( FILE * , char *) ;
int main( int argc , char *argv[] )
{
	FILE *fp ;

	if( argc == 1)
		Pgprint(stdin,"Standard Input") ;
	else{
		while(--argc){
			if( (fp=fopen(*++argv,"r")) == NULL ){
				fprintf(stderr,"\n%s: FIle access denied or does not exist",*argv) ;
				exit(1) ;
			}
			else{
				Pgprint(fp,*argv) ;
				fclose(fp) ;
			}
		}
	}
	return 0 ;
}

void Pgprint( FILE *fp , char *name)
{
	char *Line = NULL , end = '\n'; 
	unsigned lineno = 1, pgno = 1 ;
	ssize_t foot = 0;

	printf("\t\t\t\t\t--%s--\n",name) ;
	while( (foot = getline(&Line,&WRDCNT,fp)) != 0 ){
		if( lineno == 1 )
			printf("\t\t\t\t\t--Page %d--\n",pgno) ;
		// if( strchr(Line,'\n')){
		// 	foot = 0 ;
		// 	continue ;
		// }
		if( foot == -1 )
			break ;
		printf("%d. %s",lineno++,Line) ;
		if( lineno == LNCNT ){
			printf("\t\t\t\t\t--End of Page %d--\n",pgno++) ;
			lineno = 1 ;
		}
	}
	if( foot == -1 )
		if( lineno != LNCNT ){
			int cnt = lineno ;
			for( int i = 0 ; i < (LNCNT - lineno) ; i++ )
				printf("%d\n",cnt++);
			printf("\t\t\t\t\t--Page No :%d--\n",pgno) ;
		}
}

