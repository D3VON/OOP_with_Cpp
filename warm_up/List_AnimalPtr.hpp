/*
 * List_AnimalPtr.hpp
 *
 *  Created on: May 13, 2010
 *      Author: cab10886
 */

#ifndef LIST_ANIMALPTR_HPP_
#define LIST_ANIMALPTR_HPP_
#include "Animals.hpp"


/*
 * List node;
 */
struct Node
{
	Animal* data;
	Node * next;

};

/*
 * List iterator;
 */
struct aIterator{
	Node* current;
	Animal* (*deref)(aIterator*);
	void (*next)(aIterator*);
};
Animal* iterator_deref(aIterator*);
void iterator_next(aIterator*);
void iterator_ctor(aIterator*);
/*
 * List declaration and management
 */
struct aList {
	Node* root, *tail;
	int size;
	void (*dtor)(aList*);
	void (*push_back)(aList*,Animal*);
	aIterator (*begin)(aList*);
	aIterator (*end)(aList*);
};
void dtor_helper(aIterator*);
void List_AnimalPtr_ctor(aList*);
void List_AnimalPtr_dtor(aList*);
void List_AnimalPtr_push(aList*,Animal*);
aIterator List_AnimalPtr_begin(aList*);
aIterator List_AnimalPtr_end(aList*);

int List_AnimalPtr_Iterator_equal(aIterator,aIterator);

typedef aIterator List_AnimalPtr_Iterator;
typedef aList List_AnimalPtr;

#endif /* LIST_ANIMALPTR_HPP_ */
