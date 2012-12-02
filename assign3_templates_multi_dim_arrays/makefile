PROJECT = B00135581

#Project 3, Templates
SRC_FILES =   \
	Sptr.hpp \
  	dummy.cpp \
	Makefile   \
	README

#specify the compiler -- the -g option is to enable debugging
GXX=g++ -g -Wall

# Specifiy the target
all: a.out

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable

a.out: dummy.o 
	$(GXX)  dummy.o  -o a.out

# Specify how the object files should be created from source files

dummy.o: dummy.cpp
	$(GXX)  -c  dummy.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *~ core parser_test

#This target makes a archive containing all the project source files,
#suitable for submission.
submit:	$(SRC_FILES)
	tar cvfz $(PROJECT).tar.gz $(SRC_FILES)
