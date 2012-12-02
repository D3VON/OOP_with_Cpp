/*
 * pointerTricks.cpp
 *
 *  Created on: Feb 4, 2012
 *      Author: devonmcb
 */

#include <iostream>
using namespace std;

void f(int *j);

int main(){

	int i; 
	int *p; 
	printf("Code: int i; \n");
	printf("Code: int *p; \n");
	printf("i's actual address: \n");
	printf("%x\n",&i); // i's actual address
	
	p = &i; // p points to the 'address of' i
	printf("Code: p = &i; \n");
	printf("p's actual address: \n");
	printf("%x\n",&p); // p's actual address
	 
	f(p);   // f gets the address of i via pointer p
	printf("Code: f(p); \n");
	printf("i's value: \n"); // is output after all the function's output.
	printf("%d\n",i);

	cout<<"-----------------------------------"<<endl;
	cout<<"From: http://www.codeproject.com/Articles/24684/How-to-create-Linked-list-using-C-C"<<endl;
	cout<<"-----------------------------------"<<endl;


      int a = 50;       // initialize integer variable a
	  printf("Code: int a = 50; \n");
      cout<<"Value of 'a' using '<<a' = "<<a<<endl;          // show the output of a
      cout<<"Memory address of 'a' using '<<&a': "<<&a<<endl; // show the address of a
      cout<<endl;
 
      int * b = &a;             // declare an integer pointer b
      //b = &a;              // transfer the address of 'a' to pointer 'b'
      printf("Code: int * b; \n");
      printf("Code: b = &a; \n");
	  cout<<"Value of Pointer 'b' using '<<*b': "<<*b<<endl;  // show the output of *b
      cout<<"Content of Pointer 'b' using '<<b': "<<b<<endl; // show the content of *b
      cout<<"Memory address of Pointer 'b' using '<<&b': "<<&b<<endl; // show the address of *b
      cout<<endl;
 
      int **c;                // declare an integer pointer to a pointer
      c = &b;                 // transfer the address of 'b' to 'c'
	  printf("Code: int **c; \n");
	  printf("Code: c = &b; \n");
      cout<<"can't do this: '<<***c', since c wasn't declared that 'deep'"<<endl; 
      cout<<"Value of Pointer 'c' using '<<**c': "<<**c<<endl; // show the output of **c
      cout<<"Content of Pointer 'c' using '<<*c': "<<*c<<endl;  // show the content of **c
      cout<<"Content of Pointer 'c' using '<<c': "<<c<<endl;  // show the content of **c
      cout<<"Memory address of Pointer 'c' using '<<&c': "<<&c<<endl; // show the address of **c
      cout<<endl;

 
      int ***d;                // declare an integer pointer to a pointer
      d = &c;                 // transfer the address of 'c' to 'd'
	  printf("Code: int ***d; \n");
	  printf("Code: d = &c; \n");
      cout<<"Value of Pointer 'd' using '<<***d': "<<***d<<endl; // show the output of **d
      cout<<"Content of Pointer 'd' using '<<**d': "<<**d<<endl;  // show the content of **d
      cout<<"Content of Pointer 'd' using '<<*d': "<<*d<<endl;  // show the content of **d
      cout<<"Content of Pointer 'd' using '<<d': "<<d<<endl;  // show the content of **d
      cout<<"Memory address of Pointer 'd' using '<<&d': "<<&d<<endl; // show the address of **d
      cout<<endl;

      printf("If we do this:   int ***e; \n");
      printf("Can't do this:   e = &b; \n");
	  printf("Error message: cannot convert `int**' to `int***' in assignment\n");
      cout<<endl;


      return 0;
	  
	  
} 
	 
void f(int *j) // f gets the address of i , stores it in j pointer
{ 
  // j is acting as if it was p now. 
  *j = 100; // store the value 100 where j points (j points to p points to i)

  // wow, I didn't expect this:
  printf("the address j's holding (and p's holding), which is i's address: \n");
  printf("%x\n",j); // the address j's holding (p's address)

  printf("the value stored (j points to p points to a value): \n");
  printf("%d\n",*j); // the value stored (j points to p points to a value)
  printf("j's own address: \n");
  printf("%x\n",&j); // j's own address

}

