#include <stdio.h>

struct keyword{
	int count ;
	int number ;
} key , keytab[10];
int main( int argc , char *argv[] )
{
	printf("%p %p" , &key , keytab ) ;
	return 0 ;
}
