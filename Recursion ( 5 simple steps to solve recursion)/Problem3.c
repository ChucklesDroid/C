//Write a function that counts the number of ways you can partition n objects using
//parts upto m (assuming m >= 0)
#include<stdio.h>

int Partition ( int n , int m ) // n = objects , m = max partition size
{
  if( n == 0 )
   return 1 ;
  else if( m == 0 || n < 0)
   return 0 ;
  else
   return Partition( n , m - 1) + Partition(n - m , m ) ;
}
main()
{
  int object_count  , max_partition_size ;
   printf("Enter value of n and m :") ;
   scanf("%d %d" , &object_count , &max_partition_size ) ;
   printf("\n No of ways : %d " , Partition (object_count , max_partition_size ) );
   
  return 0 ;
}