/*
 * Animals.cpp
 *
 *  Created on: September 15, 2010
 *      Author: Devon McBride, dmcbrid1@binghamton.edu or devonmcb@yahoo.com
 *  Assignment: cs440, "warm-up"
 */

#include "Animals.hpp"
#include <stdio.h>

Dog* Dog_new(const char* name, int tag)///////////////////////////////////
{
	Dog* doggy = new Dog();
	doggy->animal.number_of_legs = 4;
	doggy->dog_tag_number = tag;
	doggy->animal.talk = &talk_dog;
	doggy->fetch = &Dog_fetch;
	doggy->animal.delet = &Dog_delet;
	doggy->name = name;
	doggy->animal.type_name = "Dog";
	return doggy;
}

Dog *Animal_downcast_Dog(Animal *a){
	const char* s = "Dog";
	if(a->type_name == s){
		void* vptr = (void*) a;
		Dog* dptr = (Dog*) vptr;
		return dptr;
	}
	return 0;
}
Fish *Fish_new(const char *name)
{
	Fish* ptr = new Fish();
	ptr->animal.talk = &Fish_talk;
	ptr->swim = &Fish_swim;
	ptr->animal.delet = &Fish_delet;
	ptr->animal.name = name;
	ptr->animal.number_of_legs = 0;
	ptr->animal.type_name = "Fish";
	return ptr;
}
Fish * Animal_downcast_Fish(Animal *a)
{
	const char* s = "Fish";
	if(a->type_name == s){
		void* vptr = (void*) a;
		Fish* fptr = (Fish*) vptr;
		return fptr;
	}
	return 0;
}

void talk_dog(Animal* a)
{
	const char* n = "Dog";
	if (a->type_name == n)
	{
		std::cout << "Woof!\n";
	}
}

void Fish_talk(Animal* a)
{
	const char* n = "Fish";
	if (a->type_name == n)
	{
		std::cout << "Gurgle!\n";
	}
}

void Dog_delet(Animal* a)
{
	Dog* doggy = Animal_downcast_Dog(a);
	delete doggy;
}

void Fish_delet(Animal* a)
{
	Fish* fishy = Animal_downcast_Fish(a);
	delete fishy;
}

void Dog_fetch(Dog* d)
{
	const char* n = "Dog";
	if (d->animal.type_name == n)
	{
		std::cout << "Fetching...\n";
	}
}

void Fish_swim(Fish* f)
{
	const char* n = "Fish";
	if(f->animal.type_name == n)
	{
		std::cout << "Swimming...\n";
	}
}
