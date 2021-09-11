#include <stdio.h>
main()
{
    int fahr=300 ;
    for(fahr; fahr >= 0 ; fahr-=20)
    printf("%d\t%f\n",fahr,((5.0/9.0)*(fahr-32)));
    
}