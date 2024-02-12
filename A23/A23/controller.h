#pragma once

#include "domain.h"
#include "dynarray.h"


typedef int (*filterFunc)(void* elem, void* param);
struct Controller {
	struct Repo* repo;

	DArray* undo;
	DArray* redo;

};

struct Controller* controller_init();

void controller_destr(struct Controller* contr);

int add_to_controller(struct Controller* contr, char nam[20], Concentration concentration, int quantity, int price);

int remove_from_controller(struct Controller* contr, char nam[20],Concentration concentration);

int update_controller(struct Controller* contr, char nam[20], Concentration concentration, int quantity, int price);

int stringsearch(Medicine* med, char* string);

DArray* displayArray(struct Controller* contr, void*, filterFunc);

DArray* display_short_quantity(struct Controller* contr,int quantity);


int undoChange(struct Controller* contr);
int redoChange(struct Controller* contr);

void testController();




