// references versus pointers 

// using swap() as an example
#include <iostream>
using namespace std;

void swapP(int *a, int*b)
{
	int temp; 

	temp = *a;

	*a = *b;

	*b = temp;

}

void swapR(int &x, int&y)
{
	int temp;
               // very clean, simple syntax.  NICE!
	temp = x;

	x = y; 

	y = temp;

}

int main()
{
	int woof = 5;
	int meow = 9;
	cout<<"woof is: "<<woof<<", meow is: "<<meow<<endl;

	swapP(&woof, &meow);
	cout<<"woof is: "<<woof<<", meow is: "<<meow<<endl;

	swapR(woof, meow); // very simple, clean style passing args
	cout<<"woof is: "<<woof<<", meow is: "<<meow<<endl;

	return 0;

}
