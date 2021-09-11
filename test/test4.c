#include<stdio.h>
char Arr[10] = {1} ;
//int someFunction()
//{      
// return Arr ;
//}    

int main(int argc, char ** argv)  
{ 
  printf("argc = %d\n" , argc ) ;
  printf("*argv[] = %s" , *++argv) ;
  return 0;  
}