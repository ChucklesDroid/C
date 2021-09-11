#include<stdio.h>
/*For printing ASCII values from 75 to 100*/
main()
{
  int ch=75;
  while(ch<=100)
  {
  printf("ASCII value = %d\tSYMBOL = %c\n",ch,ch);
  ch++;
  }
}