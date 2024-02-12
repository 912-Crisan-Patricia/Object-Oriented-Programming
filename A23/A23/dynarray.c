#pragma once

#include "domain.h"
#include "dynarray.h"
#include <stdlib.h>


//Creates on heap an instance of DynArray and returns a pointer to it
//(func-function that deallocates the elements stored ina array, cpfunc- function that deepcopies element from array) ->  pointer to DynArray

DArray* array_init(desF func, copyF cpfunc)
{

	DArray* array;
	array = (DArray*)malloc(sizeof(DArray));

	if (array == NULL)
		return NULL;

	array->capacity = 2;
	array->size = 0;
	array->list = (TElem*)malloc(array->capacity * sizeof(TElem));

	if (array->list == NULL)
		return NULL;

	array->elemFunction = func;
	array->copyFunction = cpfunc;


	return array;

}

//deallocates the memory reserved for an instance in array
void array_destr(DArray* array)
{
	for (int i = 0; i < array->size; i++)
		array->elemFunction(array->list[i]);
	free(array->list);
	free(array);
}


DArray* copyArray(DArray* copy)
{
	DArray* dest = array_init(copy->elemFunction, copy->copyFunction);
	for (int i = 0; i < copy->size; i++)
	{
		TElem elem = copy->copyFunction(copy->list[i]);
		add_to_array(dest,elem);
	}
	return dest;
}

//getters
TElem* getList(DArray* array)
{
	return array->list;
}
int getSize(DArray* array)
{
	return array->size;
}


//adds in the array the element elem at the end
int add_to_array(DArray* array, TElem elem)
{
	if (array == NULL)
		return -1;

	if (array->size == array->capacity)
	{
		int newCapacity = array->capacity * 2;
		TElem* newList = realloc(array->list, newCapacity * sizeof(TElem));

		if (newList == NULL)
			return -1;


		array->capacity = newCapacity;
		array->list = newList;

	}
	if(array->list == NULL)
		return -1;

	array->list[array->size++] = elem;
	return 0;

}

//removes an element from array using an index for specified element 
int remove_from_array(DArray* array, int index)
{
	if(index >= array->size)
		return -1;

	array->elemFunction(array->list[index]);
	for (int i = index; i < array->size-1; i++)
		array->list[i] = array->list[i + 1];
	array->size--;


	if (array->size * 4 <= array->capacity)
	{
		int newCapacity = array->capacity / 2;
		TElem* newList = realloc(array->list, array->capacity * sizeof(TElem));

		if (newList == NULL)
			return -1;

		array->capacity = newCapacity;
		array->list = newList;
	}

	return 0;
}


//updates an element in array using an index for specified element
int update_array_element(DArray* array, TElem elem, int index)
{
	if (index >= array->size)
		return -1;

	array->elemFunction(array->list[index]);

	array->list[index] = elem;
	return 0;
}


//tests

#include <assert.h>
#include <string.h>

void f1(TElem e) {}
TElem f2(TElem e) { TElem e1 = 0; return e1; }

void test_array_init()
{
	DArray* testarray = array_init(f1, f2);
	assert(testarray->capacity == 2);
	assert(testarray->size == 0);
	assert(testarray->elemFunction== f1);
	assert(testarray->copyFunction== f2);


	array_destr(testarray);

}

void test_array_add()
{
	DArray* arrayadd = array_init(destroyMedicine, copyMedicine);
	Medicine* med = createMedicine("Paracetamol", "10mg", 100, 15);

	add_to_array(arrayadd, med);

	assert(strcmp(getName(arrayadd->list[0]), "Paracetamol")==0); 
	assert(strcmp(getConcentration(arrayadd->list[0]), "10mg")==0);
	assert(getQuantity(arrayadd->list[0]) == 100);
	assert(getPrice(arrayadd->list[0]) == 15);

	array_destr(arrayadd);
}

void test_array_remove()
{
	DArray* arrayremove = array_init(destroyMedicine, copyMedicine);
	Medicine* med = createMedicine("Paracetamol", "10mg", 100, 15);
	add_to_array(arrayremove, med);

	assert(arrayremove->size == 1);

	remove_from_array(arrayremove, 0);
	assert(arrayremove->size == 0);

	array_destr(arrayremove);

}

void test_update_array()
{
	DArray* arrayupdate = array_init(destroyMedicine, copyMedicine);
	Medicine* med = createMedicine("Paracetamol", "10mg", 100, 15);
	Medicine* med2 = createMedicine("Paracetamol", "10mg", 75, 30);


	add_to_array(arrayupdate, med);

	update_array_element(arrayupdate, med2, 0);

	assert(strcmp(getName(arrayupdate->list[0]), "Paracetamol") == 0);
	assert(strcmp(getConcentration(arrayupdate->list[0]), "10mg") == 0);
	assert(getQuantity(arrayupdate->list[0]) == 75);
	assert(getPrice(arrayupdate->list[0]) == 30);


	array_destr(arrayupdate);

}

void testDynArray()
{
	test_array_init(); 
	test_array_add();
	test_array_remove();
	test_update_array(); //all work
}
