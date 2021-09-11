#include <stdio.h>
#include <math.h>
main()
{
    int t=0,rem,no,arm=0,temp,count=0;
    printf("Enter No- ");
    scanf("%d",&no);
    temp=no;
    while(temp)
     {
       count++;
       temp=temp/10;
     }
    printf("%d\n",count);
    temp=no;
    while(temp)
     {
         rem=temp%10;
         t=pow(rem,count);
         printf("%d",rem);
         printf("  %d",t);
         arm+=pow(rem,count);
         printf("\t%d\n",arm);
         temp=temp/10;
     }
    printf("\n%d",arm);
    if(arm==no)
     printf("\nIt is a armstrong no");
    else
     printf("\nIt is not a armstrong no");
}