#include<stdio.h>
/*print temp in f and c from 0,20,40.....300'F*/
main()
{
  float celc,fahr=900.0;
  printf("Fahrenheit to Celcius\n");
  while(fahr<=2000.0)
  {
    celc=(5.0/9.0)*(fahr-32.0);    
    printf("%f\t%3.0f\n",fahr,celc);
    fahr+=20.0;
  }

}
/*main()
{
  int celc,fahr=0;
  while(fahr<=300)
  {
    celc=5*(fahr-32)/9;    
    printf("%d\t%d\n",fahr,celc);
    fahr+=20;
  }

}INTEGER DIVISION TRUNCATION OCCURS FOR 5 / 9(=0) 
BUT BY USING FLOAT AND 5.0/9.0 WE WORK AROUND IT BY 
USING CALC = 5 * (FAHR - 32) / 9  */