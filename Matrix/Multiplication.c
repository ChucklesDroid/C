#include <stdio.h>
int main()
{
    int Arr_size ;
    printf("Enter size of matrix -") ;
    scanf("%d" , &Arr_size) ;
    
    int Arr_Matrix1[Arr_size][Arr_size] , Arr_Matrix2[Arr_size][Arr_size] , Arr_index , Arr_Prod[Arr_size][Arr_size] , Arr_index2 ;
    printf("\nEnter Array 1 - ") ;
    for(Arr_index = 0 ; Arr_index < Arr_size ; Arr_index ++ )
    {
        scanf( "%d",&Arr_Matrix1[Arr_index] );
    }
        printf("\nEnter Array 2 - ") ;
    for(Arr_index = 0 ; Arr_index < Arr_size ; Arr_index ++ )
    {
        scanf( "%d",&Arr_Matrix2[Arr_index] );
    }

    //Multiplying matrices
    for(Arr_index = 0 ; Arr_index < Arr_size ; Arr_index++ )
    {
        for(Arr_index2 = 0 ; Arr_index2 < Arr_size ; Arr_index2++ )
        
    }

}