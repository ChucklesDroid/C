#include <stdio.h>
int main()
{
    int fahr;
    for(fahr = 0;fahr <= 200;fahr+=20)
        printf("%d\t%f\n",fahr,(5.0/9.0)*(fahr-32));
}