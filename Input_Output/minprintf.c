#include<stdio.h>
#include<string.h>
#include<stdarg.h>

void minprintf( char *, ... );
int main( int argc , char *argv[] )
{
	int ival = 10 ;	
	float fval = 2.5 ;
	char *sval = "Aakarsh" ;
	minprintf("Value of ival = %d",ival) ;
	minprintf("Value of fval = %f",fval) ;
	minprintf("Value of sval = %s",sval) ;
	return 0 ;
}

void minprintf( char *fmt , ... )
{
	va_list ap ;
	char *p , *sval;
	int ival ;
	float fval ;
	va_start( ap , fmt ) ;

	for( p = fmt ; *p ; p++ ){
		if( *p != '%' ){
			putchar(*p) ;
			continue ;
		} else
			break ;
	}

	switch( *(++p))
	{
		case 'd' : ival = va_arg( ap , int ) ;
			  	   printf("%d",ival) ;
			       break ;
		case 'f' : fval = va_arg( ap , double ) ;
			   	   printf("%f" , fval);
			       break ;
		case 's' : sval = va_arg( ap , char * ) ;
			       puts( sval ) ;
			       break ;
		default :  putchar('%') ;
			       putchar(*p) ;
			       break ;
	}
	va_end(ap) ;	
}
