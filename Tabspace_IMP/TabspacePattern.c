//Answer on site :- https://stackoverflow.com/questions/17269109/how-many-spaces-are-considered-in-t
//Solution:-
//in C99 and C11,\t ( horizontal tab ) Moves the active position to the 
//next horizontal tabulation position on the current line(usually 8 or 4 here 
//value is 8). If the active position is at or past the last defined horizontal 
//tabulation position, then if past tabulation position it moves the next character
//after'\t' to next tabulation position like- 8,16,24,32,40....so on.
#include <stdio.h>
#include <math.h>

int func = 10 ;
int main(void)
{
  int a , b;
  printf("%d%d%d%d%d%d%d%d\t%d",1,2,3,4,5,6,7,8,9) ;
  printf("%d",printf("hello%d\t",scanf("%d%d",&a,&b))); 
  printf("%d",printf("hello\t%d",scanf("%d%d",&a,&b)));
  printf("%d",printf("\thello%d",scanf("%d%d",&a,&b)));
  return 0 ;
}

