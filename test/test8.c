#include <stdio.h>
#include <string.h>
#define BUFFMAX 1000
#define CNTRYMAX 5

void printArr(char *arr[]){
    for (int i = 0; i < CNTRYMAX ; i++)
        printf("%c\t", arr[i]);
    printf("\n");
}
int main()
{
  char swap[2];
//   printf("Enter 5 integers: ");
//   for (int i = 0; i < 5; i++)
//     scanf("%c", &array[i])
;
  char *array[5];
  char a[20] , b[20] , c[20] , d[20] , e[20 ];
  a[0] = 't' ;
  b[0] = 'e' ;
  c[0] = 's' ;
  d[0] = 'd' ;
  e[0] = 'r' ;
 // passing base address of arrays to  pointer to pointer
  array[0] = a ; array[1] = b ; array[2] = c ; array[3] = d ; array[4] = e; 
  
  for (int i = 0 ; i < CNTRYMAX ; i++){
    printf("After %d pass ",i+1);
    printArr(array);
    for (int j = 0 ; j < CNTRYMAX - i - 1; j++){
      if ( strcmp(array[j], array[j+1]) ){
        strcpy(swap,array[j]);
        strcpy(array[j],array[j+1]);
        strcpy(array[j+1],swap);
      }
    }
  }
  printf("Sorted Array");
  printArr(array);
  return 0;
}

