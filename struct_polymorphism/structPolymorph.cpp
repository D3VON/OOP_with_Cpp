#include <iostream>
#include <time.h>
#include <stdio.h>

using namespace std;

struct x
{
	int x;
};

void foo(char *s)
{
  printf("%s\n", s);
}


struct y
{
	struct x *X;
	int *y;
};

int main(int argc, char *argv[])
{
	printf("Hello, world\n");

/*
                        printf("0 \n");
                    sleep(1);
	y Z;
                        printf("1 \n");
                    sleep(2);
	  Z.X->x = 10; // sometimes works; sometimes segfaults.  Don't know why.
                    sleep(3);

                        printf("2 \n");
                    sleep(1);
	printf("%d \n",Z.X->x);
                    sleep(1);
                        printf("3 \n");


char *p;
char array[20];
printf("%zd, %zd, %zd\n", sizeof p, sizeof array, sizeof "hello");
*/
  


	return 0;
}
