#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#define FMTMAX 100
#define SMAX 100

void minscanf(char *, ... ) ;
int main(void)
{	
	char str[SMAX] ;
	int ival ;
	minscanf("%s",str) ;
	minscanf("%d",&ival) ;
	printf("%s",str) ;
	printf("\n%d",ival) ;
	return 0 ;
}

void minscanf( char *fmt , ... ) 
{
	double *dval ;
	char localfmt[FMTMAX],*p ,*sval ;
	va_list ap ;
	int i = 0 , *ival ;
	//float *fval ;
	va_start( ap , fmt ) ;

	for( p = fmt ; *p != '\0' ; p++ , i++ ){
		if( *p != '%' ){
			localfmt[i] = *p ;
			continue ;
		} 

		if( p != fmt )
			i++ ;

		for( ; isalnum(*p) || *p == '%' ; i++ , p++ )
			if( isalpha(*p)){
				localfmt[i] = *p ;
				if( *p == 'l' || *p == 'h' )
					continue ;
				else
					break ;
			} else 
				localfmt[i] = *p ;
		
		switch( *p )
		{
			case 'd' : localfmt[++i] = '\0' ;
				   ival = va_arg( ap , int *) ;
				   scanf(localfmt,ival) ;
				   break ;
		  	case 'f' : localfmt[++i] = '\0' ;
				   dval = va_arg( ap , double *) ;
				   scanf(localfmt,dval) ;
				   break ;
			case 's' : localfmt[++i] = '\0' ;
				   sval = va_arg(ap,char *) ;
				   scanf(localfmt,sval);
				   break ;
			default :  scanf(localfmt,sval);
				   break ;
		}
		i=0 ;
	} va_end(ap) ;
}
