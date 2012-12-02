#include <stdio.h>
#include <iostream>

#define FUNCPOINTERSASARGS_HPP

int (*pt2Function)(float, char, char) = NULL;       

int DoIt(float a, char b, char c){ printf("DoIt\n");   return a+b+c; }
int DoMore(float a, char b, char c){ printf("DoMore\n"); return a-b+c; }

// 2.6 How to Pass a Function Pointer
              // TAKES A FUNCTION POINTER AS PARAMETER
// <pt2Func> is a pointer to a function which returns an int and takes a float and two char
void PassPtr(int (*pt2Func)(float, char, char))
{
   int result = (*pt2Func)(12, 'a', 'b');     // call using function pointer
   cout << result << endl;
}
// execute example code - 'DoIt' is a suitable function like defined above in 2.1-4
void Pass_A_Function_Pointer()
{
   cout << endl << "Executing 'Pass_A_Function_Pointer'" << endl;
   PassPtr(&DoIt); // PASS FUNCTION POINTER AS ARG
}