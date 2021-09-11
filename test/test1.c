#include <stdio.h>
int main()
{int a ,b ;
int *ptr1 , *ptr2 ;
*ptr1 = &a ;
ptr2 = a ; // ERROR !! only for array as they are self referencing pointers
printf("%d \n" , &a ) ;
printf("%d \t %x" , *ptr1 , ptr1) ;
printf("\n%x" , ptr1) ;
printf("%x \n" , ptr2 ) ;


return 0 ;
}