/*	Node.cpp
 *
 *	practicing making a linked list with pointers and junk. 
 *
*/


#include <stdio.h>
#include <limits.h>


//#ifndef 
#define SIZEOF_MACRO_TEST(theType) node_##theType


#define ARRAY_SIZE(x) ((sizeof(x) / sizeof((x)[0]))-1)


#define ARRAY_SIZE2(str) (sizeof(str)-1)
                              
#define List_DEFINE(x) (void woof_##x(){printf("woof");})

//If you are writing a header file that must work when included in ISO C programs, write __typeof__ instead of typeof. 
#define min(x,y) ({       \
	typeof(x) _x = (x);     \
	typeof(y) _y = (y);     \
	(void) (&_x == &_y);    \
	_x < _y ? _x : _y; })
// if they're the same type? do the next line? else fail?

struct meow
{
  double two;
  double golden;
  char z;
  const char *stringy;
};

struct woof
{
  int x;
  double y;
  struct meow;
};


int main(int argc, char *argv[])
{
	printf("Hello, world\n");
  struct meow m;
  m.two = 2;
  m.golden = 1.618;
  m.z = 'z';
  m.stringy = "meow";
  struct woof w;
	printf("m.two is %f, m.golden is %f, m.z is %c\n",
          m.two, m.golden, m.z);

  // don't know how to use this: http://gcc.gnu.org/onlinedocs/gcc/Typeof.html
  //printf("%d is typeof's response for argument int", typeof (int));

	printf("min of m.two & m.golden is: %f\n", min(m.two,m.golden));

  //Get The Size of An Array of Arbitrary Type 
  //There are some instances where you don’t actually 
  //know the size of your array. This handy macro will 
  //  tell you the size of your array, i.e. how many 
  //  elements are in it:
  //#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
  //This example utilizes the sizeof operator, 
  //for more information on this refer to this article. 
  //  You can use this macro as such:

  printf("---------------length of strings via macro--------------\n");
  int data[50];
  fprintf(stdout, "Array size: %u\n",ARRAY_SIZE(data)); 

  char woof[] = "woofwoof";
  fprintf(stdout, "length of string w is: %u\n", ARRAY_SIZE(woof));
  fprintf(stdout, "length of string w is: %u\n", ARRAY_SIZE2(woof));

  int a,b;
  a=5;
  b=12;
 
  printf("---------------min of values via macro--------------\n");
  fprintf(stdout, "%u\n", min(a,b));

//Another very handy use of C macros is when commenting out code. 
//If you have already commented out a block of code using /* … */ 
//  then within that block you have another set of /* … */ and 
//  perhaps a few //. 
//You can actually just do:
#if 0
  /* comment ...
  */
   
  // code
   
  /* comment */
#endif 

	
	return 0;
}
