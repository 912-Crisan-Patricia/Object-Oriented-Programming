#include <stdlib.h>
#include <string.h>
#include "domain.h"



//Creates on heap an instance of Medicine and returns a pointer to it
Medicine* createMedicine(char nam[20], Concentration con, int quan, int pri)
{
	Medicine* m = (Medicine*)malloc(sizeof(Medicine));

	if(m== NULL)
		return NULL;	

	strcpy(m->name, nam);
	m->concentration = (Concentration)malloc((strlen(con)+1)+ sizeof(char));

	if (m->concentration == NULL)
	{
		free(m);
		return NULL;
	}
		
	strcpy(m->concentration, con);

	m->quantity = quan;
	m->price = pri;

	return m;
}


//deallocated the memory for reserved to instance of Medicine
void destroyMedicine(Medicine* med)
{
	if (med == NULL)
		return;
	free(med->concentration);
	free(med);
}

Medicine* copyMedicine(Medicine* copy )
{
	Medicine* dest = createMedicine(getName(copy), getConcentration(copy), getQuantity(copy), getPrice(copy));
	return dest;
}


//getters 

char* getName(Medicine* m) 
{
	return m->name;
}
Concentration getConcentration(Medicine* m)
{
	return m->concentration;
}
int getQuantity(Medicine* m)
{
	return m->quantity;
}
int getPrice(Medicine* m)
{
	return m->price;
}

//setters
void setName(Medicine* m, char name[20])
{
	strcpy(m->name, name);
}
void setConcentration(Medicine* m, Concentration concentration)
{
	free(m->concentration);
	m->concentration = (Concentration)malloc((strlen(concentration) + 1) * sizeof(char));
	if (m->concentration == NULL)
		return;
	strcpy(m->concentration, concentration);
}
void setQuantity(Medicine* m, int quan)
{
	m->quantity = quan;
}

void setPrice(Medicine* m, int price)
{
	m->price = price;
}

//tests

#include <assert.h>

void test_createMedicine()
{

	Medicine* med = createMedicine("paracetamol", "10mg", 10, 10);

	assert(strcmp(med->name, "paracetamol") == 0);
	assert(strcmp(med->concentration, "10mg") == 0);
	assert(med->quantity == 10);
	assert(med->price == 10);

	destroyMedicine(med);
}

void testDomain()
{
	test_createMedicine();
}