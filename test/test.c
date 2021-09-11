#include <stdio.h>
#define A(a,b)  a##b
#define B(a)  #a
#define C(a)  B(a)


int main(int argc , char *argv[])
{
    #ifdef __linux__
        printf("%s\n" , C(A(1,2))) ;
        printf("%s\n" , B(A(1,2))) ;
    #endif
    return 0 ;
}