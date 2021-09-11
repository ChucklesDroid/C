#include <stdio.h>
#include<math.h>
main()
{
    int i,rem,upper,lower,arm=0,temp,count=0;
    printf("Enter Upper Range- ");
    scanf("%d",&upper); 
    printf("\nEnter lower Range- ");
    scanf("%d",&lower);
    for(i=lower;i<=upper;i++)
    {
    temp=i;
     while(temp)
     {
       count++;
       temp=temp/10;
     }
     temp=i;
     while(temp)
     {
         rem=temp%10;
         arm+=pow(rem,count);
         temp=temp/10;
     }
     if(arm==i)
     printf("%d  ",i);
    }
}