
#include "funcPointersAsArgs.hpp"
#include <stdio.h>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{

  pt2Function = DoIt; // wow, unusually easy syntax for C.  
  
if(pt2Function >0){                           // check if initialized
   if(pt2Function == &DoIt)
      printf("Pointer points to DoIt\n"); }
else
   printf("Pointer not initialized!!\n");

// 2.5 calling a function using a function pointer
int result1 = pt2Function    (12, 'a', 'b');          // C short way
cout<<result1<<endl;
int result2 = (*pt2Function) (15, 'a', 'b');          // C
cout<<result2<<endl;


	return 0;
}
