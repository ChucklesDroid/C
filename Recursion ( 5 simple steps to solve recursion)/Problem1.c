//Program to print first n non negative numbers

#include <stdio.h>

int sum( int num )
{
    if(num == 1)
      return 1 ;
    else
      return num + sum(num - 1) ;
}
main()
{
    int Nth_num ;
      printf("Enter value of nth digit \n") ;
      scanf("%d" , &Nth_num) ;
      printf("Sum of non negative natural numbers upto n is %d" , sum(Nth_num)) ;
    
    return 0 ;
}