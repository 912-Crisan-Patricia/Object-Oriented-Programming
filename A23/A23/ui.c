#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "controller.h"
#include "dynarray.h"


void display_medicine(DArray* array)
{
	if (getSize(array) == 0)
		printf("No entries \n");

	for (int i = 0; i < getSize(array); i++)
		printf("Name: %s // Concentration %s //Quantity %d //Price %d\n", getName(getList(array)[i]),
			getConcentration(getList(array)[i]), getQuantity(getList(array)[i]), getPrice(getList(array)[i]));

}

int comparequantity(const void* a, const void* b)
{
	return getQuantity(*(TElem*)a) - getQuantity(*(TElem*)b);
}


struct UI* ui_init()
{
	struct UI* u = (struct UI*)malloc(sizeof(struct UI));

	if (u == NULL)
		return NULL;

	u->contr = controller_init();

	return u;
}

void ui_destr(struct UI* ui)
{
	controller_destr(ui->contr);
	free(ui);
}

int check_digits(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (!isdigit(str[i]))
			return -1;
	return 0;
}

//void run(struct Ui* ui)
//{
//	int ok=1;
//
//	while (ok)
//	{
//		printf("\n    Menu: \n");
//		printf("1. Add Medicine\n");
//		printf("2. Remove Medicine\n");
//		printf("3. Update Medicine\n");
//		printf("4. Display Medicines by given string, if empty, display all\n");
//		printf("5. See Medicines with short supply\n");
//		printf("6. Undo last change\n");
//		printf("7. Redo last change\n");
//		printf("0. Exit\n");
//
//		char s[50];
//		fgets(s, 50, stdin);
//		s[strlen(s) - 1] = '\0';
//
//		if (check_digits(s) < 0)
//			printf("Invalip input");
//
//		else
//		{
//			int op = atoi(s);
//			if (op == 1)
//			{
//				printf("Name:");
//				char nam[20];
//				fgets(nam, 20, stdin);
//				nam[strlen(nam) - 1] = '\0';
//
//				printf("Concentration:");
//				char concentration[20];
//				fgets(concentration, 20, stdin);
//				concentration[strlen(concentration) - 1] = '\0';
//
//				printf("Quantity:");
//				char str[20];
//				fgets(str, 20, stdin);
//				str[strlen(str) - 1] = '\0';
//				if (check_digits(str) < 0)
//					printf("Invalid quantity input\n");
//				else
//				{
//
//					int quan = atoi(str);
//					printf("Price:");
//					fgets(str, 20, stdin);
//					str[strlen(str) - 1] = '\0';
//					if (check_digits(str) < 0)
//						printf("Invalid price input\n");
//					else
//					{
//						int price = atoi(str);
//
//						int res = add_to_controller(ui->contr, nam, concentration, quan, price);
//						
//						if (res == -2)
//							printf("Medicine already in list, quanitty updated");
//						else if (res == -1)
//							printf("Something went wrong");
//						else
//							printf("Medicine added succesfully");
//
//					}
//					
//				}
//
//			}
//		}
//	}
//}

void run(struct UI* ui)
{
	while (1)
	{
		printf("\n    Menu: \n");
		printf("1. Add Medicine\n");
		printf("2. Remove Medicine\n");
		printf("3. Update Medicine\n");
		printf("4. Display Medicines by given string, if empty, display all\n");
		printf("5. See Medicines with short supply\n");
		printf("6. Undo last change\n");
		printf("7. Redo last change\n");
		printf("0. Exit\n");

		char s[50];
		fgets(s, 50, stdin);
		s[strlen(s) - 1] = '\0';
		if (check_digits(s) == -1)
			printf("Invalid option\n");
		else
		{
			int command = atoi(s);
			if (command == 1)
			{
				printf("Name: ");
				//char* nam; //- test memory leaks
				//nam = (char*)malloc(50 * sizeof(char));
				char nam[15];
				fgets(nam, 15, stdin);
				nam[strlen(nam) - 1] = '\0';

				printf("Concentration: ");
				char concentration[100];
				fgets(concentration, 100, stdin);
				concentration[strlen(concentration) - 1] = '\0';

				printf("Quantity: ");
				char str[20];
				fgets(str, 20, stdin);
				str[strlen(str) - 1] = '\0';
				if (check_digits(str) == -1)
					printf("Invalid input for quantity\n");
				else
				{
					int quantity = atoi(str);
					printf("Price: ");
					fgets(str, 20, stdin);
					str[strlen(str) - 1] = '\0';
					if (check_digits(str) == -1)
						printf("Invalid value for price\n");
					else
					{
						int price = atoi(str);

						int res = add_to_controller(ui->contr, nam, concentration, quantity, price);
						if (res == 1)
							printf("Medicine already in the list, quantity updated\n");
						else if (res == -1)
							printf("An error occurred");
						else
							printf("Medicine added successfully!\n");
					}
				}
			}
			else if (command == 2)
			{
				printf("Give name of Medicine to remove: ");
				char nam[15];
				fgets(nam, 15, stdin);
				nam[strlen(nam) - 1] = '\0';

				printf("Give concentration to remove: ");
				char concentration[100];
				fgets(concentration, 100, stdin);
				concentration[strlen(concentration) - 1] = '\0';

				if (remove_from_controller(ui->contr, nam, concentration) == -1)
					printf("Medicine not found");
				else
					printf("Medicine removed succesfully");

			}
			else if (command == 3)
			{
				printf("Name: ");
				char nam[15];
				fgets(nam, 15, stdin);
				nam[strlen(nam) - 1] = '\0';

				printf("Concentration: ");
				char concentration[100];
				fgets(concentration, 100, stdin);
				concentration[strlen(concentration) - 1] = '\0';

				printf("Quantity: ");
				char str[20];
				fgets(str, 20, stdin);
				str[strlen(str) - 1] = '\0';
				if (check_digits(str) == -1)
					printf("Invalid input for quantity\n");
				else
				{
					int quantity = atoi(str);
					printf("Price: ");
					fgets(str, 20, stdin);
					str[strlen(str) - 1] = '\0';
					if (check_digits(str) == -1)
						printf("Invalid value for price\n");
					else
					{
						int price = atoi(str);

						int res = update_controller(ui->contr, nam, concentration, quantity, price);
						if (res == -1)
							printf("Medicine doesn't exist");
						else
							printf("Medicine updated successfully!\n");
					}
				}
			}
			else if (command == 4)
			{
				printf("String to serach by (empty string will display all Medicines): ");
				char search_str[50];
				fgets(search_str, 50, stdin);
				search_str[strlen(search_str) - 1] = '\0';

				DArray* display;
				display = displayArray(ui->contr, search_str, stringsearch);
				qsort(getList(display), getSize(display), sizeof(Medicine*), comparequantity);
				display_medicine(display);
				array_destr(display);
			}
			else if (command == 5)
			{
				printf("Quantity: ");
				char str[30];
				fgets(str, 30, stdin);
				str[strlen(str) - 1] = '\0';
				if (check_digits(str) == -1)
					printf("Invalid value for quantity\n");
				else
				{
					int quan = atoi(str);
					DArray* display;
					display = display_short_quantity(ui->contr, quan);
					qsort(getList(display), getSize(display), sizeof(Medicine*), comparequantity);
					display_medicine(display);
					array_destr(display);
				}
				
			}
			else if (command == 6)
			{
				if (undoChange(ui->contr) == -1)
					printf("List already in initial form\n");
				else
					printf("Last change was successfully reverted!\n");
			}
			else if (command == 7)
			{
				if (redoChange(ui->contr) == -1)
					printf("There are no changes to redo\n");
				else
					printf("Last undo was successfully reverted!\n");
			}
			else if (command == 0)
			{
				break;
			}
				
			else
				printf("Invalid option");
		}
	}
}