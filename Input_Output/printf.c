#include<stdio.h>

int main( void)
{
	char ch[12] = "Hello, World" ;
	printf("%s\n",ch) ;
	printf("%10s\n",ch) ;
	printf("%.10s\n",ch) ;
	printf("%-10s\n",ch) ;
	printf("%.15s\n",ch) ;
	printf("%-15s\n",ch) ;
	printf("%15.10s\n",ch) ;
	printf("%-15.10s\n",ch) ;
	return 0;
}
