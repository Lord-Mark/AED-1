#include <stdio.h>

int F1(unsigned int n)
{
   if (n == 0)
      return n;
   int i, j = 0, count;

   
   for(i = 1; i < ((2 * n)); i+=2){
      for(count = 0; count < i; j++, count++);
   }

   return j;
}

int main()
{
   unsigned int n = 10;
   int r;
   r = F1(n);

   printf("%d\n", r);

   return 0;
}