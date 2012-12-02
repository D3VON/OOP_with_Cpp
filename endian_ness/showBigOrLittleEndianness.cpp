/*	
 *
 *	practicing making a linked list with pointers and junk. 
 *
*/

#include <iostream>
#include <string>
using namespace std;

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


	cout<<"1 is LittleEndian, 0 is BigEndian: "<<endl<<
		    "                                   "<<whichByteOrder()<<endl;
	cout<<">How could I determine the endianness of my compile environment at"<<endl;
	cout<<">compile time, instead of run time?"<<endl;
	cout<<endl;
	cout<<"You can't write a compile-time expression to determine it, because"<<endl;
	cout<<"endianness is a property of representations, not values, and there"<<endl;
	cout<<"are no objects whose representations can be examined at compile"<<endl;
	cout<<"time."<<endl;
	cout<<endl;
	cout<<"One solution is to run a program at compile time that determines"<<endl;
	cout<<"the endianness and outputs a suitable #define to a file which"<<endl;
	cout<<"you then include."<<endl;
	cout<<endl;


		
	return 0;
}
