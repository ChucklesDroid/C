#include<stdio.h>
#define HASHSIZE 10 
/* Test Function to check order of preference */
int main( int argc , char *argv[] )
{
	char Arr[HASHSIZE] = "A" ;
	char *s = Arr;
	unsigned hashval;	
	for( hashval = 0 ; *s != '\0' ; s++ )
		hashval = *s + 31 * hashval ;
	printf("%d" , hashval ) ;	
	return 0;
}
