#ifndef PERSON_HPP
#define PERSON_HPP

/* Note that no functions are available to the user to 
 * instantiate Person or Student, and thus the user cannot
 * validly instantiate them. This is analagous to the 
 * abstract base class. Internally, you may define any 
 * functions you wish, but those would be private to 
 * your implementation.
 */

struct Person {
  const char *type_name; // stores 'deepest' derived type name
  const char *name;
  char gender;
  void (*work)(Person *);      
  void (*delet)(Person *);
};

struct Student {
  Person person;
  const char *major; 
  void (*graduate)(Student *);  
};

struct Under {
  Student student;
  int year;
};

struct Grad {
  Student student;
  const char *degree;
};

struct Professor { 
  Person person;
  const char *office;
  void (*research)(Professor *, const char*);   
};

// defined in Person.cpp, for use identifying whether downcasting possible.
extern const char *student_types[]; 
extern const char *professor_types[]; 

Student *Person_downcast_Student(Person *a);

Under *Under_new(const char *name, char gender, const char *major, int year);
Under *Person_downcast_Under(Person *);
Under *Student_downcast_Under(Student *);

Grad *Grad_new(const char *name, char gender, const char *major, const char *degree);
Grad *Person_downcast_Grad(Person *);
Grad *Student_downcast_Grad(Student *);

Professor *Professor_new(const char *name, char gender, const char *office);
Professor *Person_downcast_Professor(Person *a);

void Student_delet(Person* a);
void Professor_delet(Person* a);

#endif
