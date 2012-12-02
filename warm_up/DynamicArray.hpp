/*
 * DynamicArray.hpp
 *
 *  Created on: May 13, 2010
 *      Author: cab10886
 */

#ifndef DYNAMICARRAY_HPP_
#define DYNAMICARRAY_HPP_

#define DynamicArray_Class(TYPE) struct DynamicArray_##TYPE { \
	TYPE * arr;\
	int size, capacity;\
	const char* type; \
	TYPE & (*at)(DynamicArray_##TYPE *,int); \
	void (*resize)(DynamicArray_##TYPE *,int);\
	void (*reserve)(DynamicArray_##TYPE * , int);\
	void (*push_back)(DynamicArray_##TYPE * , TYPE);\
	void (*delet)(DynamicArray_##TYPE *);\
};

#define DynamicArray_functions(TYPE) TYPE & DynamicArray_##TYPE##_at(DynamicArray_##TYPE * list, int index)\
	{\
	return list->arr[index];\
	}\
	\
	void DynamicArray_##TYPE##_reserve(DynamicArray_##TYPE * list, int cap)\
	{\
		if(list->capacity <= cap){ \
			TYPE * newarr = new TYPE[cap];\
			for(int i = 0; i < list->size; ++i)	newarr[i] = list->arr[i]; \
			delete [] list->arr;	\
			list->arr = newarr;\
			list->capacity = cap;\
		}\
	}\
	void DynamicArray_##TYPE##_resize(DynamicArray_##TYPE * list, int size__)\
	{\
		if(size__ > list->capacity){\
			DynamicArray_##TYPE##_reserve(list, size__ * 2);\
		}\
		list->size = size__; \
	}\
	void DynamicArray_##TYPE##_push_back(DynamicArray_##TYPE * list, TYPE obj )\
	{\
		if(list->size >= list->capacity){\
			list->reserve(list, list->size * 2);\
		}\
		list->arr[++ list->size] = obj; \
	}\
	void DynamicArray_##TYPE##_delet(DynamicArray_##TYPE * list)\
	{\
		delete [] list->arr;\
	}\
	DynamicArray_##TYPE * DynamicArray_##TYPE##_new(){\
		DynamicArray_##TYPE * ptr = new DynamicArray_##TYPE();\
		ptr->size = 0; \
		ptr->capacity = 1; \
		ptr->arr = new TYPE[ptr->capacity]; \
		ptr->at = DynamicArray_##TYPE##_at; \
		ptr->resize = DynamicArray_##TYPE##_resize;\
		ptr->reserve = DynamicArray_##TYPE##_reserve;\
		ptr->push_back = DynamicArray_##TYPE##_push_back;\
		ptr->delet = DynamicArray_##TYPE##_delet;\
		ptr->type = "DynamicArray_" #TYPE ;\
		return ptr;\
	}



#define DynamicArray_DEFINE(TYPE) DynamicArray_Class(TYPE) DynamicArray_functions(TYPE)

#endif /* DYNAMICARRAY_HPP_ */
