#include <stdlib.h>
#include <string.h>
#include "controller.h"
#include "repo.h"
#include "dynarray.h"
#include "domain.h"


//creates on heap an instance of Controller with 10 entries and returns a pointer to it
struct Controller* controller_init()
{
	struct Controller* contr = (struct Controller*)malloc(sizeof(struct Controller));

	if (contr == NULL)
		return NULL;

	contr->repo = repo_init();

	Medicine* med1 = createMedicine("Paracetamol", "10mg", 10, 10);
	add_to_repo(contr->repo, med1);

	Medicine* med2 = createMedicine("Aspirin", "15mg", 20, 20);
	add_to_repo(contr->repo, med2);

	Medicine* med3 = createMedicine("Ibuprofen", "10mg", 30, 30);
	add_to_repo(contr->repo, med3);

	Medicine* med4 = createMedicine("Losartan", "7mg", 40, 40);	
	add_to_repo(contr->repo, med4);

	Medicine* med5 = createMedicine("Theraflu", "10mg", 50, 50);
	add_to_repo(contr->repo, med5);

	Medicine* med6 = createMedicine("Nurofen", "15mg", 60, 60);
	add_to_repo(contr->repo, med6);

	Medicine* med7 = createMedicine("Optineuro", "20mg", 70, 70);
	add_to_repo(contr->repo, med7);

	Medicine* med8 = createMedicine("Tusin", "25mg", 80, 80);
	add_to_repo(contr->repo, med8);

	Medicine* med9 = createMedicine("Vitamina C", "30mg", 90, 90);
	add_to_repo(contr->repo, med9);

	Medicine* med10 = createMedicine("Vitamina D", "35mg", 100, 100);
	add_to_repo(contr->repo, med10);

	contr->undo = array_init(array_destr, copyArray);

	//make pointer to dyn arrays to undo 
	DArray* array = copyArray(contr->repo->data);
	add_to_array(contr->undo, array);

	contr->redo = array_init(array_destr, copyArray);

	return contr;

}

void controller_destr(struct Controller* contr)
{
	repo_destr(contr->repo);
	array_destr(contr->undo);
	array_destr(contr->redo);
	free(contr);
}

int add_to_controller(struct Controller* contr, char nam[20], Concentration concentration, int quantity, int price)
{
	Medicine* med = createMedicine(nam, concentration, quantity, price);
	int result = add_to_repo(contr->repo, med);
	if (result == 0 || result ==1)
	{
		DArray* copy = copyArray(contr->repo->data);
		add_to_array(contr->undo, copy);

		if (getSize(contr->redo) > 0)
		{
			array_destr(contr->redo);
			contr->redo = array_init(array_destr, copyArray);
		}
	}
	return result;
}

int remove_from_controller(struct Controller* contr, char nam[20], Concentration concentration)
{
	int entries = 10;
	for (int i = 0; i < get_size_repo(contr->repo) && entries == 10; i++)
	{
		if (strcmp(getName(getMedicines(contr->repo)[i]), nam) == 0)
		{
			if (strcmp(getConcentration(getMedicines(contr->repo)[i]), concentration) == 0)
			{
				entries = delete_from_repo(contr->repo, i);
			}
		}
	}
	if (entries == 0)
	{
		DArray* copy = copyArray(contr->repo->data);
		add_to_array(contr->undo, copy);

		if (getSize(contr->redo) > 0)
		{
			array_destr(contr->redo);
			contr->redo = array_init(array_destr, copyArray);
		}
		return 0;
	}
	return -1;
}

int update_controller(struct Controller* contr, char nam[20], Concentration concentration, int quantity, int price)
{
	Medicine* med = createMedicine(nam, concentration, quantity, price);

	int result = 10;
	for (int i = 0; i < get_size_repo(contr->repo) && result == 10; i++)
	{
		if (strcmp(getName(getMedicines(contr->repo)[i]), nam) == 0)
		{
			if (strcmp(getConcentration(getMedicines(contr->repo)[i]), concentration) == 0)
			{
				result = update_repo(contr->repo, med, i);
			}
		}
	}

	if (result == 0)
	{
		DArray* copy = copyArray(contr->repo->data);
		add_to_array(contr->undo, copy);

		if (getSize(contr->redo) > 0)
		{
			array_destr(contr->redo);
			contr->redo = array_init(array_destr, copyArray);
		}
		return 0;
	}

	return -1;
}

int stringsearch(Medicine* med, char* string)
{
	if(strstr(getName(med),string)!=0)
		return 1;
	return 0;
}

DArray* displayArray(struct Controller* contr, void* str, filterFunc func)
{
	DArray* array = array_init(destroyMedicine, copyMedicine);
	if (array == NULL)
		return NULL;

	for (int i = 0; i < get_size_repo(contr->repo); i++)
	{
		if (func(getMedicines(contr->repo)[i], str) !=0)
		{
			Medicine * copy = array-> copyFunction(getMedicines(contr->repo)[i]);
			add_to_array(array, copy);
		}
	}

	return array;
}

DArray* display_short_quantity(struct Controller* contr, int quantity)
{
	DArray* array = array_init(destroyMedicine, copyMedicine);

	if(array== NULL)
		return NULL;

	for (int i = 0; i < get_size_repo(contr->repo); i++)
	{
		if (getQuantity(getMedicines(contr->repo)[i]) < quantity)
		{
			Medicine* copy = array->copyFunction(getMedicines(contr->repo)[i]);
			add_to_array(array, copy);
		}
	}
	return array;
}

int undoChange(struct Controller* contr)
{
	if (getSize(contr->undo) < 2)
		return -1;

	remove_from_array(contr->undo, getSize(contr->undo) - 1);

	DArray* copy = copyArray(contr->repo->data);
	add_to_array(contr->redo, copy);
	array_destr(contr->repo->data);
	contr->repo->data = copyArray(getList(contr->undo)[ getSize(contr->undo) - 1]);

	return 0;

}

int redoChange(struct Controller* contr)
{


	if (getSize(contr->redo) < 1)
		return -1;

	array_destr(contr->repo->data);
	contr->repo->data = copyArray(getList(contr->redo)[getSize(contr->redo) - 1]);
	remove_from_array(contr->redo, getSize(contr->redo) - 1);

	DArray* aux = copyArray(contr->repo->data);
	add_to_array(contr->undo, aux);

	return 0;
}


//tests

#include <assert.h>

void test_add_Controller()
{
	struct Controller* contr = controller_init();

	add_to_controller(contr, "Parasinus", "10mg", 10, 10);

	assert(strcmp(getName(getMedicines(contr->repo)[10]), "Parasinus") == 0);
	assert(strcmp(getConcentration(getMedicines(contr->repo)[10]), "10mg") == 0);
	assert(getQuantity(getMedicines(contr->repo)[10] ) == 10);
	assert(getPrice(getMedicines(contr->repo)[10]) == 10);

	add_to_controller(contr, "Parasinus", "10mg", 20, 10);

	assert(strcmp(getName(getMedicines(contr->repo)[10]), "Parasinus") == 0);
	assert(strcmp(getConcentration(getMedicines(contr->repo)[10]), "10mg") == 0);
	assert(getQuantity(getMedicines(contr->repo)[10]) == 30);
	assert(getPrice(getMedicines(contr->repo)[10]) == 10); //case for added quantity
}

void test_remove_Controller()
{
	struct Controller* contr = controller_init();

	add_to_controller(contr, "Parasinus", "10mg", 10, 10);

	assert(getSize(contr->repo->data) == 11);

	remove_from_controller(contr, "Parasinus", "10mg");

	assert(getSize(contr->repo->data) == 10);

	controller_destr(contr);
}

void test_update_controller()
{
	struct Controller* contr = controller_init();

	add_to_controller(contr, "Parasinus", "10mg", 10, 10);

	assert(getSize(contr->repo->data) == 11);

	update_controller(contr, "Parasinus", "10mg", 20, 20);

	assert(getQuantity(getMedicines(contr->repo)[10]) == 20);
	assert(getPrice(getMedicines(contr->repo)[10]) == 20);

	controller_destr(contr);

}

void testController()
{
	test_add_Controller();
	test_remove_Controller();
	test_update_controller();
}