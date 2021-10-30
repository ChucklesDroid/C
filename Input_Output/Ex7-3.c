#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include<ctype.h>
#define FMTMAX 100
void minprintf( char *, ... );
int main( int argc , char *argv[] )
{
	int ival = 10 ;	
	float fval = 2.5 ;
	char *sval = "Aakarsh" ;
	minprintf("Value of ival = %3d",ival) ;
	minprintf("Value of fval = %4.1f",fval) ;
	minprintf("Value of sval = %s",sval) ;
	return 0 ;
}

void minprintf( char *fmt , ... )
{
	va_list ap ;
	char *p , *sval , sfmt[FMTMAX];
	int ival , i = 0;
	float fval ;
	va_start( ap , fmt ) ;

	for( p = fmt ; *p ; p++ ){
		if( *p != '%' ){
			//putchar(*p) ;
			printf("%c",*p) ;
			continue ;
		} 
	
	for( sfmt[i] = *p ; *p != '\0' && i < FMTMAX ; i++ , p++ ){
		sfmt[i] = *p ;
		if( isalpha(sfmt[i])){
			if( sfmt[i] == 'l' && sfmt[i] == 'h')
				continue;
			else 
				break;
		}
	}
	sfmt[++i] = '\0' ;
	switch( *p)
	{
		case 'd' : ival = va_arg( ap , int ) ;
			  	   //sprintf(sfmt,"%s%c",sfmt,*p) ;
				   printf(sfmt,ival) ;
			       break ;
		case 'f' : fval = va_arg( ap , double ) ;
			   	   //sprintf(sfmt,"%s%c",sfmt,*p) ;
				   printf(sfmt , fval);
			       break ;
		case 's' : sval = va_arg( ap , char * ) ;
			       //sprintf(sfmt,"%s%c",sfmt,*p) ;
				   printf(sfmt, sval ) ;
			       break ;
		default :  putchar('%') ;
			       printf("%s%c",sfmt,*p) ;	
			       break ;
	}
	}
	va_end(ap) ;	
}
