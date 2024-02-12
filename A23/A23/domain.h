#pragma once
#pragma warning(disable : 4996)


typedef char* Concentration;

typedef struct {
	char name[20];
	Concentration concentration;
	int quantity;
	int price;

} Medicine;

Medicine* createMedicine(char nam[20], Concentration con, int quan, int pri);
void destroyMedicine(Medicine*);
Medicine* copyMedicine(Medicine*);



char* getName(Medicine* m);
Concentration getConcentration(Medicine* m);
int getQuantity(Medicine* m);
int getPrice(Medicine* m);

void setName(Medicine* m, char name[20]);
void setConcentration(Medicine* m, Concentration concentration);
void setQuantity(Medicine* m, int quan);
void setPrice(Medicine* m, int price);


void testDomain();
