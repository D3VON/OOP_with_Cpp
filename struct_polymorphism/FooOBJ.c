#include <stdio.h>
#include "FooOBJ.h"

struct fooobj {
	int privateint;
	char *privateString;
};

FooOBJ newFooOBJ(){
	FooOBJ foo=(FooOBJ)malloc(sizeof(struct fooobj));
	bzero(foo, sizeof(struct fooobj));
	return foo;
}

void setFooNumber(FooOBJ foo,int num){
	if(foo==NULL) return;  
	foo->privateint=num;
}

void setFooString(FooOBJ foo,char *string){
	if(foo==NULL) return;
	foo->privateString=string;
}

/* dump debug contents of FooOBJ to stdout */	
void dumpFooState(FooOBJ foo){
	if(foo==NULL) return;
	printf("value of private int==%d\n", foo->privateint);
        printf("value of private string==");
        if(foo->privateString == NULL){
		puts("(NULL)");
	} else {
		printf("%s\n", foo->privateString);
	}
}

void deleteFooOBJ(FooOBJ foo){
	/* dont forget to free privateString if you malloced it here!!*/
	free(foo);
}
