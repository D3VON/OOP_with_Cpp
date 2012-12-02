/*
 * dummy.cpp
 *
 *  Created on: May 7, 2012
 *      Author: devonmcb
 */
#include <iostream>
#include <string>
#include <cstring>
#include "Sptr.hpp"

using namespace std;

class A {
  public:
    A(const char * x){
    	/* ===========================================
    	 * I'm still not used to the following, having
    	 * started with scripting languages and Java.
    	 * It seems barbaric! Uncivilized! Antique!
    	 * ========================================*/
    	// new char [some-size] returns pointer
        c = new char[strlen(x) + 1]; // allocates space on heap
        strcpy(c, x); //copies characters from x into space at c
    }
    ~A(){};
    void foo(int i){
    	cout<<i<<" is an int."<<endl;
    }
  //private: // commented out for ease of testing
    char * c;
};


class B : public A {
  public:

    B() : A("B"), buf(new char[10]) {}

    ~B() { delete [] buf; }

    char * buf; // public for ease of testing here.

    void setBuf(const char * n){
		buf = new char[strlen(n) + 1];
		strcpy(buf,n);
    }

  //private: // moved to public for ease of testing
};



int main(){

	Sptr<A> s1;

	Sptr<A> s2(new A("a string"));
	cout<< "This is s2->c: "<< s2->c << endl;
	s1->foo(1);
	//cout<< "s1 has this many pointers: "<<s1.counter->count<<endl;// can't do this
	s2->foo(2);
	cout<< "s2 has this many pointers: "<<s2.counter->count<<endl;

	/********************TEST COPY CTOR***************************/
	Sptr<A> s3(s2);
	cout<< "This is s3->c: "<< s3->c << endl;
	s3->foo(3);
	cout<< "s2 has this many pointers: "<<s2.counter->count<<endl;

	Sptr<A> ap1(new A("a string"));
	Sptr<A> ap2; // Initialized to point to null pointer.

	ap1->foo(1234); // Arrow operator.
cout<<"got here 1 "<<endl;
	Sptr<B> bp1(new B);
cout<<"got here 2 "<<endl;
	Sptr<B> bp2(bp1); // Copy constructor.
cout<<"got here 3 "<<endl;

	// This is in the project assignment, but I had to remove the "Sptr<A>"
	// because ap2 was already initialized several lines above.
	//Sptr<A> ap2(bp2); // Automatic conversion to base class pointer.
	//ap2(bp2); // Automatic conversion to base class pointer.
	ap2 = bp2; // Automatic conversion to base class pointer.
cout<<"got here 4 "<<endl;

	/* COMPILE TIME ERROR:
	 * no match for call to ‘(Sptr<A>) (Sptr<B>&)’
	 */

	bp1 = bp2; // Self-assignment must be safe.
	ap1 = bp2; // Self-assignment must be safe.

	//s1(s2);// ah, this is assignment, not copy ctor; haha, duh!

	cout<<endl;
	cout<<"returned OK"<<endl;
	cout<<"==========="<<endl;
	return 0;
}
