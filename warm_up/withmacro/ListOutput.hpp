// ListPersonPtr.hpp

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "Person.hpp"
typedef Person *PersonPtr;
// Comparison function, used later.
bool
PersonPtr_less(const PersonPtr &p1, const PersonPtr &p2) {
    return strcmp(p1->name, p2->name) < 0;
}

struct Link_PersonPtr {
  Link_PersonPtr *next, *prev;
};
struct Node_PersonPtr {
  Link_PersonPtr link;
  PersonPtr p;
};
struct List_PersonPtr_Iterator
{
  Link_PersonPtr    *link;
  PersonPtr (*deref)(List_PersonPtr_Iterator*);
  void    (*inc)  (List_PersonPtr_Iterator*);
  void    (*dec)  (List_PersonPtr_Iterator*);
};
struct List_PersonPtr  {
  Link_PersonPtr head; 
  int  count;
  char type[(int)sizeof("List_PersonPtr")];
  List_PersonPtr_Iterator (*begin)     (List_PersonPtr*);
  List_PersonPtr_Iterator (*end)       (List_PersonPtr*);
  List_PersonPtr_Iterator (*push_front)(List_PersonPtr*, PersonPtr);
  List_PersonPtr_Iterator (*push_back) (List_PersonPtr*, PersonPtr);
  void (*sort)(List_PersonPtr*);
  bool (*sort_style)      (const PersonPtr &, const PersonPtr &); 
  void (*erase)(List_PersonPtr*, List_PersonPtr_Iterator);
  void (*delet)(List_PersonPtr*);
};
void FrontBackSplit_PersonPtr(struct Link_PersonPtr* source, struct Link_PersonPtr** frontRef, struct Link_PersonPtr** backRef);
struct Link_PersonPtr* SortedMerge_PersonPtr(struct Link_PersonPtr* a, struct Link_PersonPtr* b);
void MergeSort_PersonPtr(struct Link_PersonPtr** headRef)
{
  struct Link_PersonPtr* head = *headRef;
  struct Link_PersonPtr* a;
  struct Link_PersonPtr* b;
  if ((head == 0) || (head->next == 0))
  {
    return;
  }
  FrontBackSplit_PersonPtr(head, &a, &b); 
  MergeSort_PersonPtr(&a);
  MergeSort_PersonPtr(&b);
  *headRef = SortedMerge_PersonPtr(a, b);
}
void sort_PersonPtr(List_PersonPtr * list){
  list->head.prev->next = 0;
  list->head.prev = 0;
  MergeSort_PersonPtr(&(list->head.next));
  Link_PersonPtr *linky = &(list->head);
  Link_PersonPtr* head = linky;
  linky->next->prev = linky;
  linky = linky->next;
  while(linky!=0)
  {
     if (linky->next == 0)
     {
        linky->next = head;
        linky->next->prev = linky;
        break;
     }
     linky->next->prev = linky;
     linky = linky->next;
  }
}
struct Link_PersonPtr* SortedMerge_PersonPtr(struct Link_PersonPtr* a, struct Link_PersonPtr* b)
{
  struct Link_PersonPtr* result = 0;
  if (a == 0){
     return(b);
  }   
  else if (b==0){
     return(a);
  }
  if ( PersonPtr_less(
                        ((Node_PersonPtr*)(a))->p,
                        ((Node_PersonPtr*)(b))->p
                     )
     )
  {
     result = a;
     result->next = SortedMerge_PersonPtr(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge_PersonPtr(a, b->next);
  }
  return(result);
}
void FrontBackSplit_PersonPtr(struct Link_PersonPtr* source, 
struct Link_PersonPtr** frontRef, struct Link_PersonPtr** backRef)
{
  struct Link_PersonPtr* fast;
  struct Link_PersonPtr* slow;
  if (source==0 || source->next==0)
  {
    *frontRef = source;
    *backRef = 0;
  }
  else
  {
    slow = source;
    fast = source->next;
    while (fast != 0)
    {
      fast = fast->next;
      if (fast != 0)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = 0;
  }
}
void MergeSort_PersonPtr(struct Link_PersonPtr** headRef);
struct Link_PersonPtr* SortedMerge(struct Link_PersonPtr* a, struct Link_PersonPtr* b);
void FrontBackSplit(struct Link_PersonPtr* source, struct Link_PersonPtr** frontRef, 
struct Link_PersonPtr** backRef);
List_PersonPtr *List_PersonPtr_new(bool (*sort_style)
(const PersonPtr &p1, const PersonPtr &p2));
void insert_before(Link_PersonPtr *pos, Node_PersonPtr *n);
List_PersonPtr_Iterator push_front(List_PersonPtr* list, PersonPtr p);
List_PersonPtr_Iterator push_back(List_PersonPtr* list, PersonPtr p);
void inc(List_PersonPtr_Iterator *it);
void dec(List_PersonPtr_Iterator *it);
List_PersonPtr_Iterator end(List_PersonPtr* list);
List_PersonPtr_Iterator begin(List_PersonPtr* list);
PersonPtr deref(List_PersonPtr_Iterator* it);
List_PersonPtr_Iterator List_PersonPtr_Iterator_new(Link_PersonPtr* link);
void erase(List_PersonPtr* list, List_PersonPtr_Iterator it);
void List_PersonPtr_delet(List_PersonPtr* list);
List_PersonPtr *List_PersonPtr_new(bool (*sort_style)
(const PersonPtr &p1, const PersonPtr &p2))
{  
	List_PersonPtr *list = (List_PersonPtr *)malloc(sizeof(List_PersonPtr));
  list->head.next = &(list->head); 
  list->head.prev = &(list->head);
  List_PersonPtr_Iterator it = begin(list);
	list->count = 0;
  char woof[(int)sizeof("List_PersonPtr")] = "List_PersonPtr";
  strcpy(list->type, woof);
  list->begin = begin;
  list->end = end;
  list->sort = sort_PersonPtr;
  list->erase = erase;
  list->delet = List_PersonPtr_delet;
  list->sort_style = PersonPtr_less;
  list->push_front = push_front;
  list->push_back = push_back;
	return  list;
}
void List_PersonPtr_delet(List_PersonPtr* list){
  Link n = list->head.next;
  while(n != list->head){
    n = n->next;
    free(n->prev);
    n->prev = 0;
  }
  free(list->head);
  list->head = 0;
  free(list);
  list = 0;
/*
  Link n = list->head.next;\
  while(n != list->head){\
    n = n->next;\
    free(n->prev);\
    n->prev = 0;\
  }\
  free(list->head);\
  list->head = 0;\
*/
}
List_PersonPtr_Iterator push_front(List_PersonPtr* list, PersonPtr p) {
  list->count++;
  Node_PersonPtr *n = (Node_PersonPtr*)malloc(sizeof(Node_PersonPtr));
  n->p = p;     
  insert_before(list->head.next, n);
  return List_PersonPtr_Iterator_new( &(n->link) );
}
List_PersonPtr_Iterator push_back(List_PersonPtr* list, PersonPtr p) {
  list->count++;
  Node_PersonPtr *n = (Node_PersonPtr*)malloc(sizeof(Node_PersonPtr));
  n->p = p;
  insert_before(&(list->head), n);
  return List_PersonPtr_Iterator_new( &(n->link) );
}
void insert_before(Link_PersonPtr *pos, Node_PersonPtr *n) {
  n->link.next = pos;
  n->link.prev = pos->prev;
  pos->prev->next = &(n->link);
  pos->prev = &(n->link);
}
void erase(List_PersonPtr* list, List_PersonPtr_Iterator it){
  list->count--;
  it.link->next->prev = it.link->prev;
  it.link->prev->next = it.link->next;
}
List_PersonPtr_Iterator List_PersonPtr_Iterator_new(Link_PersonPtr* link){
  List_PersonPtr_Iterator it;
  it.link = link;
  it.inc = &inc;
  it.deref = &deref;
  it.dec = &dec;
  return it;
}
void inc(List_PersonPtr_Iterator *it) {
  it->link = it->link->next;
}
void dec(List_PersonPtr_Iterator *it) {
  it->link = it->link->prev;
}
bool 
List_PersonPtr_Iterator_equal( List_PersonPtr_Iterator it1, 
                               List_PersonPtr_Iterator it2)
{ 
  if (it1.link == it2.link) 
  {
    return 1;
  }
  return 0;
}
PersonPtr deref(List_PersonPtr_Iterator* it){
  return ((Node_PersonPtr*)(it->link))->p;
}
List_PersonPtr_Iterator end(List_PersonPtr* list) {
  return List_PersonPtr_Iterator_new(&(list->head));
}
List_PersonPtr_Iterator begin(List_PersonPtr* list) {
  return List_PersonPtr_Iterator_new(list->head.next);
}
