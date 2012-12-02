#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	char *s = (char*) malloc(10);
															cout<<"char *s = (char*) malloc(10);"<<endl;
	strcpy(s, "hello");
															cout<<"strcpy(s, \"hello\");"<<endl;
	free(s);
															cout<<"free(s);"<<endl;
															cout<<"-----------------------------"<<endl;
	printf("%s\n",s);
															cout<<"-----------------------------"<<endl;
															cout<<"printf(\"%s\n\",s);"<<endl;
	
	return 0;
}





// For the assignment:

// Upcast
Base *b = (Base *) derived_ptr;
// Downcast
Derived *d = Base_downcast_Derived(base_ptr);

// In C++. (can't use in assignment)
Base *b = derived_ptr; // If public inheritance.
Derived *d = dynamic_cast<Derived *>(b); // Polymorphic
Derived *d = static_cast<Derived *>(b); // Not polymorphic