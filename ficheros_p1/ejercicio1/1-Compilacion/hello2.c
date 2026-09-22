/*
Use "gcc --save-temps hello2.c" in order to save all of the intermediate files used during compilation
The .i file is the final precompiled version of the source file, with includes being resolved, comments erased, and defines being replaced in the actual code.
In this case for example, the a = min(a,b) call gets replaced with:
  a = ( (a<b)?a:b );
*/
#include <stdio.h>

#define N 5

#define min(x,y) ( (x<y)?x:y )
int a = 7;
int b = 9;
int main() {

 char* cad = "Hello world";
 int i;

 for (i=0;i<N;i++) {
   printf("%s \t a= %d b= %d\n",cad,a,b);
   a++;
   a = min(a,b);
 }
 return 0;
}
