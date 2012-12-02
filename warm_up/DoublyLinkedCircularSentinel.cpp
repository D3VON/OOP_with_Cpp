#include "DoublyLinkedCircularSentinel.hpp"
#include <stdio.h>
#include <stdlib.h>     /* declares malloc() */
#include <string.h>

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
  char *type;
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

List_PersonPtr *List_PersonPtr_new(bool PersonPtr_less(const Person*, const Person*));
void insert_before(Link *pos, Node *n);
//void remove_node(Node *n);

//Doubly-Linked, Circular Lists with Sentinel
void push_front(List_PersonPtr* list, Person* p);
void push_back(List_PersonPtr* list, Person* p);

Link head = {&head, &head};



// container constructor for PersonPtr, MyClass, int, & Stress
// substitute @@@@ for those types of objects via the macro
List_PersonPtr *List_PersonPtr_new(bool PersonPtr_less(const Person*, const Person*))
{
	List_PersonPtr *list = (List_PersonPtr *)malloc(sizeof(List_PersonPtr));
	list->l = head;
	list->count = 0;
  strncpy (list->type, "List_PersonPtr", (int) sizeof("List_PersonPtr"));
    
  list->sort = PersonPtr_less;
  list->push_front = &push_front;
  list->push_back = &push_back;
  //implementation of sort lives in test.cpp, where this 
  //struct will be part of a huge macro

	return  list;
}

//   push_front(list, p1)
void push_front(List_PersonPtr* list, Person* p) {
  Node *n = (Node*)malloc(sizeof(Node));
  n->p = p;
  insert_before(list->l.next, n);
}

void push_back(List_PersonPtr* list, Person* p) {
  Node *n = (Node*)malloc(sizeof(Node));
  n->p = p;
  insert_before(&list->l, n);
}


void insert_before(Link *pos, Node *n) {
  n->link.next = pos;
  n->link.prev = pos->prev;
  pos->prev->next = &(n->link);
  pos->prev = &(n->link);
}
void remove_node(Node *n) {
  n->link.next->prev = n->link.prev;
  n->link.prev->next = n->link.next;
}

struct Iterator
{
  Link *link;
};

//Increment becomes:
void inc(Iterator *it) {
  it->link = it->link->next;
}

//End becomes:
Iterator end() {
  Iterator it;
  it.link = &head;
  return it;
}

// Link head = {&head, &head};

//Begin becomes:
Iterator begin() {
  Iterator it;
  it.link = head.next;
  return it;
}
#endif