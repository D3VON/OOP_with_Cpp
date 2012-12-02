/*	Node.cpp
 *
 *	practicing making a linked list with pointers and junk. 
 *
 *  Created on: Feb 4, 2012
 *      Author: devonmcb
*/

#include <iostream>
#include <string>
using namespace std;

class Node
{
	public:
		float amount;
		int date; // phony for simplicity of this exercise
		//#include <string> using namespace std;
		string descrip;

		Node *next, *prev;

		Node(){};

		Node(float a, 
			 int d, 
			 string s, 
			 Node* p, Node* n)  // copy constructor
			: amount(a), date(d), descrip(s), prev(p), next(n) 
		{};

		Node(float a, 
			 int d, 
			 string s
			)
			: amount(a), date(d), descrip(s) 
		{};
};
/* WITHOUT THAT SEMICOLON AFTER THE BRACKET, i GET THIS ERROR: (WHY??????)
> g++ Node.cpp                                                  =========
Node.cpp:46: error: new types may not be defined in a return type
Node.cpp:46: note: (perhaps a semicolon is missing after the definition of `Node')
Node.cpp:46: error: extraneous `int' ignored
Node.cpp:46: error: `main' must return `int'
*/

int main(int argc, char *argv[])
{

	Node *head = new Node();

	Node *temp = new Node(19.95, 1, "paint",0,0);

	head->next = temp;
	temp->prev = head;

	printf("%i\n",head); // just the address, I guess
	printf("%i\n",head->next); // just the address, I guess
	printf("%f, on %i, Item: %s\n",temp->amount,temp->date,temp->descrip.c_str()); // just the address, I guess
	/* BIG ERROR NOTE FOR THE ABOVE LINE:
	 * temp->descrip is a c-style string, apparently, so, 
	 * it cannot be fed into the printf(%s) function.  Or the other way
	 * around--this is so bloody annoying not knowing the billion and a 
	 * half miniscule differences between C and C++.  What shite!
	 * ANYWAYS, you have to add .c_str() to the variable (very java-style)
	 * What a freekin' mess!  Vive la C++!
	 */
	 cout<<temp->amount<<", on "<<temp->date<<" name: "<<temp->descrip<<endl;
	 //FOLLOWUP NOTE: the above line works fine without ugly modification.
		
	return 0;
}
