#include<stdio.h>
#define swap(t,x,y) \
{ t temp ;          \
  temp = x ;        \
  x = y ;           \
  y = temp ;        \
}

int main( int argc , char *argv[])
{
 int x = 1 ;
 int y = 2 ;
 swap(int , x , y) ;
 printf("x=%d y=%d" , x , y) ;
 return 0 ;
}