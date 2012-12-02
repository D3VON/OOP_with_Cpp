typedef struct fooobj * FooOBJ;
FooOBJ newFooOBJ();
void setFooNumber(FooOBJ,int);
void setFooString(FooOBJ,char *); 
void dumpFooState(FooOBJ);  /* dump debug contents of FooOBJ to stdout */
void deleteFooOBJ(FooOBJ);
