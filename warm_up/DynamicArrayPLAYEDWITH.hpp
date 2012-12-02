/*
 * DynamicArray.hpp
 *
 *  Created on: May 13, 2010
 *      Author: cab10886
 */

#ifndef List_HPP_
#define List_HPP_

#define List_Class(PersonPtr) struct List_PersonPtr { \
	PersonPtr * arr;\
	int size, capacity;\
	const char* type; \
	PersonPtr & (*at)(List_PersonPtr *,int); \
	void (*resize)(List_PersonPtr *,int);\
	void (*reserve)(List_PersonPtr * , int);\
	void (*push_back)(List_PersonPtr * , PersonPtr);\
	void (*delet)(List_PersonPtr *);\
};

#define List_functions(PersonPtr) PersonPtr & List_PersonPtr_at(List_PersonPtr * list, int index)\
	{\
	return list->arr[index];\
	}\
	\
	void List_PersonPtr_reserve(List_PersonPtr * list, int cap)\
	{\
		if(list->capacity <= cap){ \
			PersonPtr * newarr = new PersonPtr[cap];\
			for(int i = 0; i < list->size; ++i)	newarr[i] = list->arr[i]; \
			delete [] list->arr;	\
			list->arr = newarr;\
			list->capacity = cap;\
		}\
	}\
	void List_PersonPtr_resize(List_PersonPtr * list, int size__)\
	{\
		if(size__ > list->capacity){\
			List_PersonPtr_reserve(list, size__ * 2);\
		}\
		list->size = size__; \
	}\
	void List_PersonPtr_push_back(List_PersonPtr * list, TYPE obj )\
	{\
		if(list->size >= list->capacity){\
			list->reserve(list, list->size * 2);\
		}\
		list->arr[++ list->size] = obj; \
	}\
	void List_PersonPtr_delet(List_PersonPtr * list)\
	{\
		delete [] list->arr;\
	}\
	List_PersonPtr * List_PersonPtr_new(){\
		List_PersonPtr * ptr = new List_PersonPtr();\
		ptr->size = 0; \
		ptr->capacity = 1; \
		ptr->arr = new TYPE[ptr->capacity]; \
		ptr->at = List_PersonPtr_at; \
		ptr->resize = List_PersonPtr_resize;\
		ptr->reserve = List_PersonPtr_reserve;\
		ptr->push_back = List_PersonPtr_push_back;\
		ptr->delet = List_PersonPtr_delet;\
		ptr->type = "List_" #TYPE ;\
		return ptr;\
	}



#define List_DEFINE(TYPE) List_Class(TYPE) List_functions(TYPE)

#endif /* List_HPP_ */
