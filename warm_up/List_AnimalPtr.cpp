/*
 * List_AnimalPtr.cpp
 *
 *  Created on: May 13, 2010
 *      Author: cab10886
 */

#include "List_AnimalPtr.hpp"

Animal* iterator_deref(aIterator* iter)
{
	return iter->current->data;
}
void iterator_next(aIterator* iter)
{
	iter->current = iter->current->next;
}
void iterator_ctor(aIterator* iter)
{
	iter->deref = &iterator_deref;
	iter->next = &iterator_next;
}
void List_AnimalPtr_ctor(aList* lst)
{
	lst->size = 0;
	lst->root = 0;
	lst->dtor = &List_AnimalPtr_dtor;
	lst->push_back = &List_AnimalPtr_push;
	lst->begin = &List_AnimalPtr_begin;
	lst->end = &List_AnimalPtr_end;
	lst->tail = 0;
}
void List_AnimalPtr_dtor(aList* lst)
{
	aIterator iter = lst->begin(lst);
	dtor_helper(&iter);
	lst->size = 0;
	lst->root = 0;
	lst->dtor = 0;
	lst->push_back = 0;
	lst->begin = 0;
	lst->end = 0;
	lst->tail = 0;
}
void dtor_helper(aIterator* iter){
	if(iter->current != 0){
		iter->next(iter);
		dtor_helper(iter);
	}
	delete iter->current;
}

void List_AnimalPtr_push(aList* lst,Animal* a)
{
	if(lst->root == 0)
	{
		lst->root = lst->tail = new Node();
	}
	else
	{
		lst->tail->next = new Node();
		lst->tail = lst->tail->next;
	}
	lst->tail->data = a;
	lst->tail->next = 0;
	++ lst->size;
}
aIterator List_AnimalPtr_begin(aList* lst)
{
	aIterator iter;
	iter.current = lst->root;
	iter.deref = &iterator_deref;
	iter.next = &iterator_next;
	return iter;
}
aIterator List_AnimalPtr_end(aList* lst)
{
	aIterator iter;
	iter.current = lst->tail;
	return iter;
}
int List_AnimalPtr_Iterator_equal(aIterator it1,aIterator it2)
{
	return it1.current == it2.current;
}

