#include <stdio.h>
/* macros for casting to parent types */
#define MIDDLE_TO_BASETYPE(ptr) (&(ptr)->base)
#define DERIVED_TO_MIDDLE(ptr) (&(ptr)->base)
#define DERIVED_TO_BASETYPE(ptr) (DERIVED_TO_MIDDLE(MIDDLE_TO_BASETYPE(ptr)))




/* example C struct hierarchy */
typedef struct BaseType {
  int foo;
} BaseType;

typedef struct Middle {
  BaseType base;
  int bar;
} Middle;

typedef struct Derived {
  Middle base;
  int baz;
} Derived;




int main(int argc, char *argv[])
{
	printf("Hello, world\n");

	Derived d;

	d.baz = 10;

	printf("%d\n", d.baz);

	BaseType *b = DERIVED_TO_BASETYPE(&d);

	printf("%d\n", b->foo);

	printf("%d\n", DERIVED_TO_BASETYPE(&d)->foo);  // OK, this is amazing

	
	return 0;
}
