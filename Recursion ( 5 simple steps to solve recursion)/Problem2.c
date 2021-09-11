//Program that takes two input n and m and outputs the number of unique paths from
//left corner to bottom right corner of a n x m grid .
//Constraints : You can only move down or rignt 1 unit at a time 

#include<stdio.h>

int Paths(row_index , column_index)
{
    if( row_index == 1 || column_index == 1 )
     return 1 ;
    else
     return Paths(row_index - 1 , column_index  ) + Paths( row_index , column_index - 1) ; }

main()
{
  int row_grid , column_grid ;
    printf("Enter values of n and m for n x m grid : -") ;
    scanf("%d%d" , &row_grid , &column_grid) ;
  //Printing Result  
    printf("\n Total paths possible under given constraints : %d " ,Paths(row_grid , column_grid) ) ;
  
  return 0 ;
}