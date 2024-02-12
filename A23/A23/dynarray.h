#pragma once

#include "domain.h"

typedef void* TElem;
typedef void (*desF)(TElem);
typedef TElem (*copyF)(TElem);

typedef struct {
	int capacity;
	int size;
	TElem* list;
	desF elemFunction;
	copyF copyFunction;

}DArray;



DArray* array_init(desF func, copyF cpfunc); //done
void array_destr(DArray* array);
DArray* copyArray(DArray* copy);


TElem* getList(DArray* array);
int getSize(DArray* array);
int add_to_array(DArray* array, TElem elem);
int remove_from_array(DArray* array, int index);
int update_array_element(DArray* array, TElem elem, int index);

void testDynArray();




