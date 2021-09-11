#include <stdio.h>
int main()
{
    int row_index , column_index ;
    int ROW_MAX , COLUMN_MAX ;

    printf("Enter max no of rows to be printed : - ") ;
    scanf("%d" , &ROW_MAX ) ;
    COLUMN_MAX = 2*ROW_MAX ;

    for ( row_index = 0 ; row_index < ROW_MAX ; row_index++ )
    {
        for ( column_index = 0 ; column_index < COLUMN_MAX ; column_index++ )
        {
            if( column_index >= (ROW_MAX-row_index) && column_index <= (ROW_MAX+row_index) )
              printf("\t*");
            else
              printf("\t");
        }

        printf("\n");
    }
}