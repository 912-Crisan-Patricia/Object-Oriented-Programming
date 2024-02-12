#include <stdlib.h>
#include <string.h>
#include "repo.h"
#include "domain.h"


//creates on heap an instance of Repo and returns a pointer to it
struct Repo* repo_init()
{
	struct Repo* repo;
	repo = (struct Repo*)malloc(sizeof(struct Repo));

	if (repo == NULL)
		return NULL;

	repo->data = array_init(destroyMedicine, copyMedicine);

	return repo;
}

//deallocates the memory reserved for an instance of Repo
void repo_destr(struct Repo* repo)
{
	if (repo == NULL)
		return;
	array_destr(repo->data);
	free(repo);
}

TElem* getMedicines(struct Repo* repo)
{
	if (repo == NULL)
		return NULL;
	return getList(repo->data);
}

int get_size_repo(struct Repo* repo)
{
	return getSize(repo->data);
}

//adds Medicine to the repository and if the element is already in repository, we'll update the quantity by adding the new quantity to the old one
int add_to_repo(struct Repo* repo, Medicine* elem)
{
	for (int i = 0; i < repo->data->size; i++)
	{
		if (strcmp(getName(getList(repo->data)[i]), getName(elem)) == 0)
		{
			if (strcmp(getConcentration(getList(repo->data)[i]), getConcentration(elem)) == 0)
			{
				setQuantity(getList(repo->data)[i], getQuantity(elem) + getQuantity(getList(repo->data)[i]));

				//setQuantity(getList(repo->data)[i], getQuantity(elem) ; //update without adding old quantity to new one
				return 1;
			}
		}
	}

	return add_to_array(repo->data, elem);
}


//deletes a Medicine from the repository

int delete_from_repo(struct Repo* repo, int index)
{
	return remove_from_array(repo->data, index);
}

//updates Medicine from the repository
int update_repo(struct Repo* repo, Medicine* elem, int index)
{
	return update_array_element(repo->data, elem, index); //why is it not working

}



//tests

#include <assert.h>

void test_add_to_repo()
{
	struct Repo* repo = repo_init();
	Medicine* elem = createMedicine("Paracetamol", "10mg", 10, 10);

	add_to_repo(repo, elem);

	assert(strcmp(getName(getList(repo->data)[0]), "Paracetamol") == 0);
	assert(strcmp(getConcentration(getList(repo->data)[0]), "10mg") == 0);
	assert(getQuantity(getList(repo->data)[0]) == 10);
	assert(getPrice(getList(repo->data)[0]) == 10);

	Medicine* elem2 = createMedicine("Paracetamol", "10mg", 20, 10);
	add_to_repo(repo, elem2);

	assert(strcmp(getName(getList(repo->data)[0]), "Paracetamol") == 0);
	assert(strcmp(getConcentration(getList(repo->data)[0]), "10mg") == 0);
	assert(getQuantity(getList(repo->data)[0]) == 30);
	assert(getPrice(getList(repo->data)[0]) == 10);

	repo_destr(repo);
}

void test_remove_from_repo()
{
	struct Repo* repo = repo_init();
	Medicine* elem = createMedicine("Paracetamol", "10mg", 10, 10);

	add_to_repo(repo, elem);

	assert(repo->data->size == 1);
	delete_from_repo(repo, 0);
	assert(repo->data->size == 0);

	repo_destr(repo);

}

void test_update_from_repo()
{
	struct Repo* repo= repo_init();
	Medicine* elem = createMedicine("Paracetamol", "10mg", 10, 10);
	Medicine* elem1 = createMedicine("Paracetamol", "10mg", 20, 11); //inflation sucks


	add_to_repo(repo, elem);
	update_repo(repo, elem1, 0);

	assert(strcmp(getName(getList(repo->data)[0]), "Paracetamol") == 0);
	assert(strcmp(getConcentration(getList(repo->data)[0]), "10mg") == 0);
	assert(getQuantity(getList(repo->data)[0]) == 20);
	assert(getPrice(getList(repo->data)[0]) == 11);

	repo_destr(repo);


}


void testRepo()
{
	test_add_to_repo();
	test_remove_from_repo();
	test_update_from_repo();
}