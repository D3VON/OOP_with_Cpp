// ListStress.hpp

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "Person.hpp"
typedef Person *Stress;
// Comparison function, used later.
bool
Stress_less(const Stress &p1, const Stress &p2) {
    return strcmp(p1->name, p2->name) < 0;
}

#ifndef LISTStress_HPP
#define LISTStress_HPP


//////////////////////////////////////////////////////////////////////////////
////////////////////// begin inserted 'list' functionality
//////////////////////////////////////////////////////////////////////////////

//Head pointer, circular:
struct Link {
  Link *next, *prev;
};


struct Node {
  Link link;
  Stress p;
};

struct List_Stress_Iterator
{
  Link    *link;
  Stress (*deref)(List_Stress_Iterator*);
  void    (*inc)  (List_Stress_Iterator*);
  void    (*dec)  (List_Stress_Iterator*);
  //void    (*erase)  (List_Stress_Iterator*);
};

struct List_Stress  {
  Link head; 
  int  count; // number of nodes
  char type[(int)sizeof("List_Stress")];

  List_Stress_Iterator (*begin)     (List_Stress*);
  List_Stress_Iterator (*end)       (List_Stress*);
  List_Stress_Iterator (*push_front)(List_Stress*, Stress);
  List_Stress_Iterator (*push_back) (List_Stress*, Stress);
  void (*sort)(List_Stress*);
  bool (*sort_style)      (const Stress &, const Stress &);  
  //implementation of sort lives in test.cpp, where this 
  //struct will be part of a huge macro
  void (*erase)(List_Stress*, List_Stress_Iterator);
  void (*delet)(List_Stress*);
};

void MergeSort(struct Link** headRef);
struct Link* SortedMerge(struct Link* a, struct Link* b);
void FrontBackSplit(struct Link* source,
                    struct Link** frontRef, 
                    struct Link** backRef);

void sort(List_Stress * list){

  //has to be called this way: list->sort(list);

  // and maybe use:            list.sortstyle

  // 'break' the circularity of the list to work in MergeSort()
  list->head.prev->next = 0;       // last node's next de-linked from sentinel
  list->head.prev = 0;             // sentinel's prev de-linked from last node

  MergeSort(&(list->head.next));   // accessing first value of list->head, 
                                   // which is actually 'next's value, which
                                   // points to the next node (first node)
  
  // REPAIRING 'broken' circular list's prev pointers & sentinel
  Link *linky = &(list->head);     // point to head/sentinel
  Link* head = linky;              // save head/sentinel
  linky->next->prev = linky;       // re-establish 1st node's prev to sentinel
  linky = linky->next;             // advance to 1nd node
  while(linky!=NULL)
  {
     printf("%s \n", ((Node*)(linky))->p->name);

     if (linky->next == NULL)      // if found end of list...
     {
        linky->next = head;        // reestablish link to sentinel
        linky->next->prev = linky; // make sentinel point to last node
        break; // doubly linked circular with sentinel fully reestablished
     }

     linky->next->prev = linky;    // reestablish next node's prev 
     linky = linky->next;          // advance to next node
  }
  // doubly linked circular with sentinel fully reestablished

        /*
          for testing

              printf("calling print(list);\n");
              print(list);

              // Backwards 
              printf("--------traversing backwards proving 'prev' links work ----------\n");
              Link* heady = &(list->head);
              for (Link *l = heady->prev; l != heady; l = l->prev) {
                // Do something with (Link *) l.
                Node* n = (Node*)l;
                printf("<<<<<<<<< %s\n", n->p->name);
              }
        */
}



void insert_before(Link *pos, Node *n);
//void remove_node(Node *n);
List_Stress_Iterator push_front(List_Stress* list, Stress p);
List_Stress_Iterator push_back(List_Stress* list, Stress p);
void inc(List_Stress_Iterator *it);
void dec(List_Stress_Iterator *it);
//void List_Stress_Iterator_delet(List_Stress_Iterator *it);
List_Stress_Iterator end(List_Stress* list);
List_Stress_Iterator begin(List_Stress* list);
Stress deref(List_Stress_Iterator* it);
List_Stress_Iterator List_Stress_Iterator_new(Link* link);
void erase(List_Stress* list, List_Stress_Iterator it);
void List_Stress_delet(List_Stress* list);


// container constructor for Stress, MyClass, int, & Stress
// substitute @@@@ for those types of objects via the macro
List_Stress *List_Stress_new(bool (*sort_style)(const Stress &p1, const Stress &p2))
{
	List_Stress *list = (List_Stress *)malloc(sizeof(List_Stress));
  list->head.next = &(list->head); 
  list->head.prev = &(list->head);
  List_Stress_Iterator it = begin(list);
	list->count = 0;
  strcpy(list->type, "List_Stress");//list->type = "List_Stress";
  list->begin = begin;
  list->end = end;
  list->sort = &sort;
  list->erase = erase;  
  list->delet = List_Stress_delet;
  list->sort_style = Stress_less; 
  list->push_front = push_front;
  list->push_back = push_back;
	return  list;
}

void List_Stress_delet(List_Stress* list){
  //free(list->head); // won't compile
  //free((void*)list->count); // this crap never works
  //free((void*)list->type); // this crap never works
  free(list);
}

//   push_front(list, p1)
List_Stress_Iterator push_front(List_Stress* list, Stress p) {
  list->count++;
  Node *n = (Node*)malloc(sizeof(Node));
  n->p = p;     
  insert_before(list->head.next, n);
          //printf("Test insertion into list: \n");
          //printf("inserting %s \n", n->p->name);
          //printf("%s was inserted\n", ((Node*)(list->head.next))->p->name);
  // BIG POINT LEARNED: to access nodes' data when you only have a Link
  // object, cast the Link object to be a Node object.  Nodes are constructed
  // such that Link objects are their first data members, so Links can be cast
  // to Nodes.  Except the 'head' (sentinel) link.
  return List_Stress_Iterator_new( &(n->link) );
}

List_Stress_Iterator push_back(List_Stress* list, Stress p) {
  list->count++;
  Node *n = (Node*)malloc(sizeof(Node));
  n->p = p;
  insert_before(&(list->head), n);
  return List_Stress_Iterator_new( &(n->link) );
}


void insert_before(Link *pos, Node *n) {
  n->link.next = pos;
  n->link.prev = pos->prev;
  pos->prev->next = &(n->link);
  pos->prev = &(n->link);
}
                              
void erase(List_Stress* list, List_Stress_Iterator it){
                      // iterator points to the one we're removing
  list->count--;

  // link prev to next
  it.link->next->prev = it.link->prev;
  it.link->prev->next = it.link->next;
}


List_Stress_Iterator List_Stress_Iterator_new(Link* link){
  List_Stress_Iterator it;
  it.link = link;
  it.inc = &inc;
  it.deref = &deref;
  it.dec = &dec;
  //it.erase = &List_Stress_Iterator_delet;
  return it;
}

/*
void List_Stress_Iterator_delet(List_Stress_Iterator it)
{
  List_Stress_Iterator* iter = &it;
  free(iter->link);
  free(iter);
}
*/

//inc is increment
void inc(List_Stress_Iterator *it) {
  it->link = it->link->next;
}

//dec is increment
void dec(List_Stress_Iterator *it) {
  //printf("%p, %p", it->link, it->link->prev);
  it->link = it->link->prev;
  //printf("%p", it->link);
}

bool 
List_Stress_Iterator_equal( List_Stress_Iterator it1, 
                               List_Stress_Iterator it2)
{ 
  //took me a very long time to realize I had to access
  //data member .link in the iterator.  
  if (it1.link == it2.link) 
  {
    return 1;   //1 if true and 0 if false
  }
  return 0;
}

// deref() returns what the iterator was pointing to.
//Person *p = it.deref(&it);
Stress deref(List_Stress_Iterator* it){
  return ((Node*)(it->link))->p;   // ((Node*)(l))->value
}

//end
List_Stress_Iterator end(List_Stress* list) {
  return List_Stress_Iterator_new(&(list->head));
}

//begin
List_Stress_Iterator begin(List_Stress* list) {
  return List_Stress_Iterator_new(list->head.next);
}
/* test.cpp provides a function to print
void print(List_Stress* list)
{                          int x = 1;
  Link* head = (Link*)list; // s.t.'s screwy here; seg faults at end of list                                                    
  printf("I'm in print()\n");
  for (Link *l = list->head.next; l != head; l = l->next) {
                           printf("----------------->%d\n", x++);
    printf("%s\n", ((Node*)l)->p->name);
                           printf("----------------->%d\n", x++);
    if ()
    {
    }
  }
}
*/

//////////////////////////////////////////////////////////////////////////////
////////////////////// end of inserted 'list' functionality
/////////////////////    (and iterator)


/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  &&&&&&&&&&&&&&&&&&&&&&&&&&&  mergesort functionality  &&&&&&&&&&&&&&&&&&&&&&&
   &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

 
// This MergeSort code substantially modeled after that found online at:
// http://www.geeksforgeeks.org/archives/7740
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct Link** headRef)
{
  struct Link* head = *headRef; // deref that pointer to get the address of sentinel link
  struct Link* a;
  struct Link* b;
 
  //printf("%s is the head node's name\n", ((Node*)(head))->p->name);
  //printf("%s is the head.next node's name\n", ((Node*)(head->next))->p->name);
  //printf("%s is the head.next node's name\n", ((Node*)(head))->p->name);
  // the above works b.c. address of head is address of head->next
  //printf("%s is the head.prev node's name field====================\n", ((Node*)(head->prev))->p->name);
  // this last stmt designed to fail: it should point to sentinel, which has no data

  //1) If head is NULL or there is only one element 
  //in the Linked List, then return.
  // Base case -- length 0 or 1 
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
 
  //2) Else divide the linked list into two halves.
  // a and b are two halves 
  /* Split head into 'a' and 'b' sublists 
     --a and b are empty when passed to FrontBackSplit, 
     and get their addresses populated when in that function.*/
  printf("calling FrontBackSplit(head, &a, &b); \n");
  FrontBackSplit(head, &a, &b); 

                        //printf("calling   MergeSort(&a); \n");
  // Recursively sort the sublists
  MergeSort(&a);
                        //printf("calling   MergeSort(&b); \n");
  MergeSort(&b);
 
  // merge the two sorted lists together 
  *headRef = SortedMerge(a, b);
}
 
struct Link* SortedMerge(struct Link* a, struct Link* b)
{
  struct Link* result = NULL;
 
  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
 
  /* Pick either a or b, and recur */
  if ( 
        Stress_less(         // returns true if alphabetical order
                        ((Node*)(a))->p, // e.g. jane
                        ((Node*)(b))->p  // e.g. mike
                      )
     )
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}

/* Split the Links of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra Link should go in the front list.
     (which means the front list will be longer instead of the back one)
     Uses the fast/slow pointer strategy.  */
void FrontBackSplit(struct Link* source, struct Link** frontRef, struct Link** backRef)
{                             // head                 //a                        //b
  //printf("%s is the head node's name\n", ((Node*)(source))->p->name);
  struct Link* fast;
  struct Link* slow;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two Links, and advance 'slow' one Link */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}
 
#endif //LISTStress_HPP

