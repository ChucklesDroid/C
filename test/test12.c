#include<stdio.h>

int main( int argc , char *argv[] )
{
	char str[5]="Back" ;
	char *p = str ;
	printf("%p\n",str) ;
	printf("%s\n",str) ;
	printf("%s\n",p) ;
	printf("\n%c", *p++ ) ; 
	printf("\nSuccess") ;
	return 0;
}
