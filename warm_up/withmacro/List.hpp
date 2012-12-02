/*
 * List.hpp
 *
 *  Created on: February 29, 2012
 *      Author: Devon McBride
 *    B-number: B00135581
 */
#ifndef List_HPP
#define LIST_HPP

#define List_DEFINE(TYPE) \
struct Link_##TYPE {\
  Link_##TYPE *next, *prev;\
};\
struct Node_##TYPE {\
  Link_##TYPE link;\
  TYPE p;\
};\
struct List_##TYPE##_Iterator\
{\
  Link_##TYPE    *link;\
  TYPE (*deref)(List_##TYPE##_Iterator*);\
  void    (*inc)  (List_##TYPE##_Iterator*);\
  void    (*dec)  (List_##TYPE##_Iterator*);\
};\
struct List_##TYPE  {\
  Link_##TYPE head; \
  int  count;\
  char type[(int)sizeof("List_"#TYPE)];\
  List_##TYPE##_Iterator (*begin)     (List_##TYPE*);\
  List_##TYPE##_Iterator (*end)       (List_##TYPE*);\
  List_##TYPE##_Iterator (*push_front)(List_##TYPE*, TYPE);\
  List_##TYPE##_Iterator (*push_back) (List_##TYPE*, TYPE);\
  void (*sort)(List_##TYPE*);\
  bool (*sort_style)      (const TYPE &, const TYPE &);\
  void (*erase)(List_##TYPE*, List_##TYPE##_Iterator);\
  void (*delet)(List_##TYPE*);\
};\
void FrontBackSplit_##TYPE(struct Link_##TYPE* source, struct Link_##TYPE** frontRef, struct Link_##TYPE** backRef);\
struct Link_##TYPE* SortedMerge_##TYPE(struct Link_##TYPE* a, struct Link_##TYPE* b);\
void MergeSort_##TYPE(struct Link_##TYPE** headRef)\
{\
  struct Link_##TYPE* head = *headRef;\
  struct Link_##TYPE* a;\
  struct Link_##TYPE* b;\
  if ((head == 0) || (head->next == 0))\
  {\
    return;\
  }\
  FrontBackSplit_##TYPE(head, &a, &b); \
  MergeSort_##TYPE(&a);\
  MergeSort_##TYPE(&b);\
  *headRef = SortedMerge_##TYPE(a, b);\
}\
void sort_##TYPE(List_##TYPE * list){\
  list->head.prev->next = 0;\
  list->head.prev = 0;\
  MergeSort_##TYPE(&(list->head.next));\
  Link_##TYPE *linky = &(list->head);\
  Link_##TYPE* head = linky;\
  linky->next->prev = linky;\
  linky = linky->next;\
  while(linky!=0)\
  {\
     if (linky->next == 0)\
     {\
        linky->next = head;\
        linky->next->prev = linky;\
        break;\
     }\
     linky->next->prev = linky;\
     linky = linky->next;\
  }\
}\
struct Link_##TYPE* SortedMerge_##TYPE(struct Link_##TYPE* a, struct Link_##TYPE* b)\
{\
  struct Link_##TYPE* result = 0;\
  if (a == 0){\
     return(b);\
  }   \
  else if (b==0){\
     return(a);\
  }\
  if ( TYPE##_less(\
                        ((Node_##TYPE*)(a))->p,\
                        ((Node_##TYPE*)(b))->p\
                     )\
     )\
  {\
     result = a;\
     result->next = SortedMerge_##TYPE(a->next, b);\
  }\
  else\
  {\
     result = b;\
     result->next = SortedMerge_##TYPE(a, b->next);\
  }\
  return(result);\
}\
void FrontBackSplit_##TYPE(struct Link_##TYPE* source, \
struct Link_##TYPE** frontRef, struct Link_##TYPE** backRef)\
{\
  struct Link_##TYPE* fast;\
  struct Link_##TYPE* slow;\
  if (source==0 || source->next==0)\
  {\
    *frontRef = source;\
    *backRef = 0;\
  }\
  else\
  {\
    slow = source;\
    fast = source->next;\
    while (fast != 0)\
    {\
      fast = fast->next;\
      if (fast != 0)\
      {\
        slow = slow->next;\
        fast = fast->next;\
      }\
    }\
    *frontRef = source;\
    *backRef = slow->next;\
    slow->next = 0;\
  }\
}\
void MergeSort_##TYPE(struct Link_##TYPE** headRef);\
struct Link_##TYPE* SortedMerge(struct Link_##TYPE* a, struct Link_##TYPE* b);\
void FrontBackSplit(struct Link_##TYPE* source, struct Link_##TYPE** frontRef, \
struct Link_##TYPE** backRef);\
List_##TYPE *List_##TYPE##_new(bool (*sort_style)\
(const TYPE &p1, const TYPE &p2));\
void insert_before(Link_##TYPE *pos, Node_##TYPE *n);\
List_##TYPE##_Iterator push_front(List_##TYPE* list, TYPE p);\
List_##TYPE##_Iterator push_back(List_##TYPE* list, TYPE p);\
void inc(List_##TYPE##_Iterator *it);\
void dec(List_##TYPE##_Iterator *it);\
List_##TYPE##_Iterator end(List_##TYPE* list);\
List_##TYPE##_Iterator begin(List_##TYPE* list);\
TYPE deref(List_##TYPE##_Iterator* it);\
List_##TYPE##_Iterator List_##TYPE##_Iterator_new(Link_##TYPE* link);\
void erase(List_##TYPE* list, List_##TYPE##_Iterator it);\
void List_##TYPE##_delet(List_##TYPE* list);\
List_##TYPE *List_##TYPE##_new(bool (*sort_style)\
(const TYPE &p1, const TYPE &p2))\
{  \
	List_##TYPE *list = (List_##TYPE *)malloc(sizeof(List_##TYPE));\
  list->head.next = &(list->head); \
  list->head.prev = &(list->head);\
  List_##TYPE##_Iterator it = begin(list);\
	list->count = 0;\
  char woof[(int)sizeof("List_"#TYPE)] = "List_"#TYPE;\
  strcpy(list->type, woof);\
  list->begin = begin;\
  list->end = end;\
  list->sort = sort_##TYPE;\
  list->erase = erase;\
  list->delet = List_##TYPE##_delet;\
  list->sort_style = TYPE##_less;\
  list->push_front = push_front;\
  list->push_back = push_back;\
	return  list;\
}\
void List_##TYPE##_delet(List_##TYPE* list){\
  /*free(list->type);*/\
	while(list->count != 0)\
		erase(list, begin(list));\
  free(list);\
}\
List_##TYPE##_Iterator push_front(List_##TYPE* list, TYPE p) {\
  list->count++;\
  Node_##TYPE *n = (Node_##TYPE*)malloc(sizeof(Node_##TYPE));\
  n->p = p;     \
  insert_before(list->head.next, n);\
  return List_##TYPE##_Iterator_new( &(n->link) );\
}\
List_##TYPE##_Iterator push_back(List_##TYPE* list, TYPE p) {\
  list->count++;\
  Node_##TYPE *n = (Node_##TYPE*)malloc(sizeof(Node_##TYPE));\
  n->p = p;\
  insert_before(&(list->head), n);\
  return List_##TYPE##_Iterator_new( &(n->link) );\
}\
void insert_before(Link_##TYPE *pos, Node_##TYPE *n) {\
  n->link.next = pos;\
  n->link.prev = pos->prev;\
  pos->prev->next = &(n->link);\
  pos->prev = &(n->link);\
}\
/* overloading OK b.c. signature different */\
void erase(List_##TYPE* list, List_##TYPE##_Iterator it){\
  list->count--;\
  it.link->next->prev = it.link->prev;\
  it.link->prev->next = it.link->next;\
  /*free((Node_##TYPE*)it.link);*/\
  free(it.link);\
}\
List_##TYPE##_Iterator List_##TYPE##_Iterator_new(Link_##TYPE* link){\
  List_##TYPE##_Iterator it;\
  it.link = link;\
  it.inc = &inc;\
  it.deref = &deref;\
  it.dec = &dec;\
  return it;\
}\
void inc(List_##TYPE##_Iterator *it) {\
  it->link = it->link->next;\
}\
void dec(List_##TYPE##_Iterator *it) {\
  it->link = it->link->prev;\
}\
bool \
List_##TYPE##_Iterator_equal( List_##TYPE##_Iterator it1, \
                               List_##TYPE##_Iterator it2)\
{ \
  if (it1.link == it2.link) \
  {\
    return 1;\
  }\
  return 0;\
}\
TYPE deref(List_##TYPE##_Iterator* it){\
  return ((Node_##TYPE*)(it->link))->p;\
}\
List_##TYPE##_Iterator end(List_##TYPE* list) {\
  return List_##TYPE##_Iterator_new(&(list->head));\
}\
List_##TYPE##_Iterator begin(List_##TYPE* list) {\
  return List_##TYPE##_Iterator_new(list->head.next);\
}

#endif 
