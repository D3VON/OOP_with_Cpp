#include "Person.hpp"
#include <string.h>

#ifndef DOUBLYLINKEDCIRCULARSENTINEL_HPP
#define DOUBLYLINKEDCIRCULARSENTINEL_HPP
#if 0
//Head pointer, circular:
struct Link {
  Link *next, *prev;
};

struct Node {
  Link link;
  Person *p;
  int value;
};

struct List_PersonPtr  {
  Link l; // constructor initializes to head 
  int count; // number of nodes
  char *type;//[sizeof("List_PersonPtr")] = "List_PersonPtr";
  void (*push_front)(List_PersonPtr*, Person*);
  void (*push_back)(List_PersonPtr*, Person*);
  bool (*sort)(const Person*, const Person*);  
  //implementation of sort lives in test.cpp, where this 
  //struct will be part of a huge macro
};


// Comparison function, used later.  // 1 if true and 0 if false
bool PersonPtr_less(const Person* p1, const Person* p2) {
    return strcmp(p1->name, p2->name) < 0;
}


//extern bool PersonPtr_less(const Person*, const Person*);

List_PersonPtr *List_PersonPtr_new(bool (*PersonPtr_less)(const Person*, const Person*));
//void insert_before(Link *pos, Node *n);
//void remove_node(Node *n);
#endif
#endif

