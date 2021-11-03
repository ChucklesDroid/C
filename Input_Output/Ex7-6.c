#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define STRMAX 100

void filecmp( FILE * , FILE * ) ;
int main( int argc , char *argv[] )
{
	FILE *fp1 , *fp2 ;
	if( argc != 3 ){
		fprintf(stderr,"Program compares two files.Pass appropriate number of files") ;
		exit(1) ;
	}
	if((fp1 = fopen(*++argv,"r")) == NULL ){
		fprintf(stderr,"%s: file cannot be opened",*argv) ;
		exit(1) ;
	} else if((fp2 = fopen(*++argv,"r")) == NULL ){
		fprintf(stderr,"%s: file cannot be opened",*argv) ;
		exit(1) ;
	} else {
		filecmp(fp1,fp2) ;
		fclose(fp1);
		fclose(fp2);
	}
	
	return 0 ;
}

void filecmp( FILE *fp1 , FILE *fp2 )
{
	char str1[STRMAX], str2[STRMAX] ;
	char *lp1 , *lp2 ;
	int val_cmp ;
	do{
		lp1 = fgets(str1,STRMAX,fp1) ;
		lp2 = fgets(str2,STRMAX,fp2) ;
		if((lp1 != NULL) && (lp2 != NULL)){
			if(strcmp(str1,str2) != 0){
				printf("\nLine sample A :\n%s",str1) ;
				printf("\nLine sample B :\n%s",str2) ;
				break ;
			}
		} else if(lp1 != NULL && lp2 == NULL){
			fprintf(stderr,"\nFile 2 encountered EOF") ;
			printf("\nLine Sample :\n%s",str1) ;
		} else if(lp2 != NULL && lp1 == NULL){
			fprintf(stderr,"File 1 encountered EOF") ;
			printf("\nLine Sample :\n%s",str2) ;
		} else{
			fprintf(stderr,"\nBoth Files encountered EOF") ;
		}
	}while(lp1 != NULL && lp2 != NULL) ;
}
