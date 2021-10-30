#include<stdio.h>
#include<string.h>

int main( int argc, char *argv[] )
{	
	char sfmt[40] = "Record value" ;
	char c = 'c';
	sprintf(sfmt,"%s%c",sfmt,c) ;	
	printf("%s",sfmt) ;	
	return 0 ;
}
