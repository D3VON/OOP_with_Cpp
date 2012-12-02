/*	Node.cpp
 *
 *	practicing making a linked list with pointers and junk. 
 *
*/
//#ifndef BUILD_NODE_NAME_BY_DEVON
#define BUILD_NODE_NAME_BY_DEVON(serialnum) node_##serialnum
//#endif
#define PRINT_TOKEN(token) printf(#token " is %d", token)


#include <iostream>
#include <string>
using namespace std;

class LinkedList
{
	private:
		class Node
		{
			public:
				float amount;
				int date; // phony 'date' for simplicity of this exercise
				string descrip;
				int position; // unreliable position-within-list marker
				Node *next, *prev;

				Node(){}

				Node(float a, 
					 int d, 
					 string s, 
					 Node* p, Node* n)  // copy constructor
					: amount(a), date(d), descrip(s), prev(p), next(n) 
				{}

				Node(float a, 
					 int d, 
					 string s
					)
					: amount(a), date(d), descrip(s) 
				{}		
		};

		Node *head;
		int number;

	public:

		LinkedList() // constructors return pointers
		{
			head = new Node();
		}
	
		void addFront(int date, float price, string desc)
		{
			Node *temp = new Node(price, date, desc);
			temp->next = head->next;
			head->next = temp;
		}
	
		void addManyGenericNodes(int number)
		{
			this->number = number;
			Node *temp = new Node(0, 0, "blank");

      while(number > 0)
      { 
				cout<<number<<endl;
        Node *BUILD_NODE_NAME_BY_DEVON(number) = temp; // implicit copy constructor
				PRINT_TOKEN(BUILD_NODE_NAME_BY_DEVON(number));

        BUILD_NODE_NAME_BY_DEVON(number)->next = head->next;
        head->next = BUILD_NODE_NAME_BY_DEVON(number);
				cout<<BUILD_NODE_NAME_BY_DEVON(number)<<endl;
				number--;
      }
		}
		
		void addBack(int date, float price, string desc)
		{
			int x = 1;
			Node *current = head;
			Node *temp = new Node(price, date, desc);
			while (current->next != 0)// just traverse to tail node
			{
				current = current->next;
				current->position = x++;
			}
			current->next = temp;
		}
		
		void displayList()
		{
			Node *temp = head;
			while (temp->next != 0)
			{
				temp = temp->next;
				cout<<"element "<<temp->position<<", cost "<<temp->amount<<", on "<<temp->date<<" name: "<<temp->descrip<<endl;
			}
		}
};

int whichByteOrder()
{
   short int word = 0x0001; //short int is 16-bit integer.
   char *byte = (char *) &word; //A char pointer points at the first 
	                              //(least-significant) byte of the integer value.
																//If the first byte of the integer is 0x01h, 
																//then the system is Little-Endian (the 0x01h 
																//is in the lowest, least-significant, address). 
																//If it is 0x00h then the system is Big-Endian.
   return(byte[0] ? 1 : 0);
}

int main(int argc, char *argv[])
{
	LinkedList *theList = new LinkedList(); //instantiation onto **heap**
	theList->addFront(1, 19.95, "soap");
	theList->addFront(4, 12.95, "paint");
	theList->addFront(4, 13.95, "sand paper");
	theList->addFront(5, 14.95, "carots");
	theList->addBack(5, 14.95, "end");
	theList->displayList();

	LinkedList theList2; //instantiation onto **stack**
	theList2.addFront(1, 19.95, "2soap");
	theList2.addFront(4, 12.95, "2paint");
	theList2.addFront(4, 13.95, "2sand paper");
	theList2.addFront(5, 14.95, "2carots");
	theList2.addBack(5, 14.95, "2end");
	theList2.addBack(5, 14.95, "2end2");
  theList2.addManyGenericNodes(8);
	//theList2.displayList();

	cout<<"1 is LittleEndian, 0 is BigEndian: "<<whichByteOrder()<<endl;
	/*

		>How could I determine the endianness of my compile environment at
		>compile time, instead of run time?

		You can't write a compile-time expression to determine it, because
		endianness is a property of representations, not values, and there
		are no objects whose representations can be examined at compile
		time.

		One solution is to run a program at compile time that determines
		the endianness and outputs a suitable #define to a file which
		you then include.

	*/


/*

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

	 //cout<<temp->amount<<", on "<<temp->date<<" name: "<<temp->descrip<<endl;
	 //FOLLOWUP NOTE: the above line works fine without ugly modification.
		
	return 0;
}
