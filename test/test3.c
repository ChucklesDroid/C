#include<stdio.h>
//#define min(file)  printf("%d%c", file ,
#define skip_spaces(p , limit)    \
do {char *lim = (limit) ;         \
      while(p < lim){             \
     if(*p++ != ' '){             \
      p-- ; break ; }}}    
while(0) 

main(void)
{char *next ;
char *p ;
//  min(32) 'p');
 if( 1)
  skip_spaces(p ,next) ;
 else
  return 1 ;
 return 0;
}