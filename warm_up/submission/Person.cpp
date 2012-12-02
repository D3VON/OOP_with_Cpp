/*
 * Person.cpp
 *
 *  Created on: February 19, 2012
 *      Author: Devon McBride, dmcbrid1@binghamton.edu or devonmcb@yahoo.com
 *  Assignment: cs440, "warm-up"
 */

#include "Person.hpp"
#include <iostream>
#include <stdlib.h>     /* declares malloc() */
#include <string.h>
#include <stdio.h>
using namespace std;

void work_student(Person* p);
void work_professor(Person* p);
void graduate(Student *s);
void Professor_research(Professor *p, const char* topic);
void Professor_delet(Person* a);
void Student_delet(Person* a);

const char *student_types[] = {"Under", "Grad"}; 
const char *professor_types[] = {"Professor"}; 
//the foregoing arrays of strings were declared in Person.hpp as 'extern'. 


Student *Person_downcast_Student(Person *a)
{        // very bad to do: if(str == "something")
  if ( strcmp(a->type_name, "Under") == 0 ||
       strcmp(a->type_name, "Grad")  == 0
     )
  {     
    Student* sptr = (Student*) a;    
		return sptr;
	}
	return 0;
}


Under *Under_new(const char *name, char gender, const char *major, int year)
{
	Under* under = (Under *)malloc(sizeof(Under));
	under->student.person.work = &work_student;
	under->student.graduate = &graduate;
	under->student.person.delet = &Student_delet;
	under->student.person.name = strdup(name);
	under->student.person.gender = gender;
  under->student.major = strdup(major);
  under->year = year;
	under->student.person.type_name = "Under";

	return under;
}


Under *Person_downcast_Under(Person *a)
{ // very bad to do: if(str == "something")
  if ( strcmp(a->type_name, "Under") == 0 )
  {
    Under* ptr = (Under*) a;
		return ptr;
	}
	return 0;
}


Under *Student_downcast_Under(Student *a)
{ // very bad to do: if(str == "something")
  if ( strcmp(a->person.type_name, "Under") == 0 )
  {
    Under* ptr = (Under*) a;
		return ptr;
	}
	return 0;
}


Grad *Grad_new(const char *name, char gender, const char *major, const char *degree)
{
	Grad* grad = (Grad *)malloc(sizeof(Grad));
	grad->student.person.work = &work_student;
	grad->student.graduate = &graduate;
	grad->student.person.delet = &Student_delet;
	grad->student.person.name = strdup(name);
	grad->student.person.gender = gender;
  grad->student.major = strdup(major);
  grad->degree = strdup(degree);  
	grad->student.person.type_name = "Grad";

	return grad;
}


Grad *Person_downcast_Grad(Person *a)
{ // very bad to do: if(str == "something")
  if ( strcmp(a->type_name, "Grad") == 0 )
  {
    Grad* ptr = (Grad*) a;
		return ptr;
	}
	return 0;
} 


Grad *Student_downcast_Grad(Student *a)
{ // very bad to do: if(str == "something")
  if ( strcmp(a->person.type_name, "Grad") == 0 )
  {
    Grad* ptr = (Grad*) a;
		return ptr;
	}
	return 0;
} 


Professor *Professor_new(const char *name, char gender, const char *office)
{
	Professor* prof = (Professor *)malloc(sizeof(Professor));
	prof->person.work = &work_professor;

	prof->person.delet = &Professor_delet;

  prof->research = &Professor_research;
	prof->person.name = strdup(name);
	prof->person.gender = gender;
	prof->person.type_name = "Professor";
  prof->office = strdup(office);
	return prof;
}



Professor *Person_downcast_Professor(Person *a)
{ // very bad to do: if(str == "something")
  if ( strcmp(a->type_name, "Professor") == 0 )
  {
    Professor* prof = (Professor*) a;
		return prof;
	}
	return 0;
} 

// Note that Grad and Under print the same thing
// for work, and so can share the implementation.
//p1->work(p1); // Prints "<name> studies <major>."
void work_student(Person* p)
{
  int x = 0;
  while (x != -1 && student_types[x] != 0 )
  { // very bad to do: if(str == "something")
    if ( strcmp(p->type_name, student_types[x]) == 0 )
    { // safe to downcast
      cout << p->name <<" studies "<< ((Student*)p)->major << ".\n";
      x = -1;
    }else{
      x++;
    }
  }
}


void work_professor(Person* p)
{
  int x = 0;
  while (x != -1 && professor_types[x] != 0 )
  { // very bad to do: if(str == "something")
    if ( strcmp(p->type_name, professor_types[x]) == 0 )
    { // safe to downcast
      cout << p->name <<" teaches."<<endl;
      x = -1;
    }else{
      x++;
    }
  }
}


// Prints "<name> graduates in <N> years and finds a job in <major>
// or goes to grad school."  Assume year 4 means one more year to
// go.
void graduate(Student *s)
{
  // IF STATEMENTS ARE ***ANATHEMA*** TO GOOD OO DESIGN!!!
  // very bad to do: if(str == "something")
  if ( strcmp(s->person.type_name, "Under") == 0 )
  { 
    int x = 5-((Under*)s)->year; // x = years left to get degree
		cout<<((Person*)s)->name <<" graduates in "<< x;
    cout<<" years and finds a job in "<<s->major<<endl;
    cout<<"or goes to grad school."<<endl;
  }
  else if ( strcmp(s->person.type_name, "Grad") == 0 )
  {    
    // Prints "<name> graduates with a <degree> and finds a job in <major>."
		cout<<((Person*)s)->name <<" graduates with a "<< ((Grad*)s)->degree;
    cout<<" and finds a job in "<<s->major<<endl;
  }else{
    //cout<< p->name <<" doesn't appear to be an undergraduate student."<<endl;
  }
}

void Professor_research(Professor *p, const char* topic)
{ // Must print "<name> does research in <topic>."
	// very bad!! const char* n = "Professor";
	// very bad!! if (p->person.type_name == "Professor")
  if (strcmp( p->person.type_name, "Professor") == 0)
	{
		cout<<p->person.name<<" does research in "<<topic<<endl;
	}
  //free((char*)n); // useless; won't work on const
}

void Student_delet(Person* a)
{
/* free is a nighmare

  // Grad, or Under specific
  // very bad for object oriented design 
  int x = 0;
  while (x != -1 && student_types[x] != 0 )
  { // very bad to do: if(str == "something")
    if ( strcmp(a->type_name, student_types[x]) == 0 )
    { 
      if (a->type_name == student_types[x])
      { // safe to downcast
        if ( strcmp(student_types[x],"Grad") == 0)
        {
          free( (void*)((Grad*)a)->degree ); 
        }
        else if ( strcmp(student_types[x],"Under") == 0) 
        {
          //free( (void*)((Under*)a)->year );
        }
        x = -1;
      }else{
        x++;
      }
    }
  }
  //student specific
       //cast to void to free strings
  free(  (void*)((Student*)a)->major );

  // person specific
  //free( (void*)a->type_name); 
  free( (void*)a->name     );
  //free( (void*)a->gender   );


  */

  free(a);
}

void Professor_delet(Person* a)
{
/*
  // Professor specific
  free((void*)((Professor*)a)->office);

  // person specific
  //free( (void*)a->type_name); //won't free
  //printf("name: %s\n", a->name);
  free( (void*)a->name     );
  //free( (void*)a->gender   );//won't free

*/

  free(a);
}
