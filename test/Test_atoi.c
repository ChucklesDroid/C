#include<stdio.h>
#include<string.h>

int main(int argc , char *argv[])
{
char s[] = "Premier League" ;
char t[] = "Manchester United" ;
char u[] = "Football" ;
char g[2][2] = { { 2,3} , {4,5} } ;
char *k[3] ;
    k[0] = s ;
    k[1] = t ;
    k[2] = u ;
    printf("\nargc = %d" , argc ) ;
   // printf("*argv[0] = %s", **argv) ;
   // printf("*argv[1] = %s", **++argv) ;
//printf("%c\n" , *( *( k + 1) + 2) );
//printf("%c\n" , (*( k + 1))[2] ) ;
//printf("\n%p" , argv ) ;
//printf("%d\n" , *(*(k + 1) ) == 'M') ;
//printf("*k = %p\n" , *k);
//printf("%c\n" , *k[0]);
//printf("%c\n" , *++k[0]);
//printf("*k = %p\n" , *k);
//printf("%c\n" , *k[1]);
//printf("%c\n" , *++k[1]);
//printf("*k = %p\n" , *k);
//printf("%c\n" , *(*(k + 1)) );
//printf("%c\n" , *(*(k + 1) + 1) );
//printf("%c\n" , *(*(k + 2)) );
//printf("%d\n" , *g[1] ) ;
//printf("%d\n" , *(g[0] + 1)) ;
//printf("%p\n" , &g) ;
//printf("%p\n" , &g[0][0]) ;
//printf("%p\n" , g[0]) ;

return 0 ;
}

