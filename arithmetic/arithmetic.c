#include<stdio.h>
main()
{
    float c,d;
    c=5 / 2 * 3.0;/*operation occurs from left to right*/
    d=3.0 * 5 / 2;/*if either of the operands is float 
    the result is in float if both operands are integers
    then result is integer */
    printf("%f\t%f",c,d);
}