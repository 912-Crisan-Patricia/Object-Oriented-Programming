#pragma once


#include "domain.h"
#include "dynarray.h"

struct Repo {

	DArray* data;
};

struct Repo* repo_init();
void repo_destr(struct Repo* repo);

TElem* getMedicines(struct Repo* repo);

int add_to_repo(struct Repo* repo, Medicine* elem);



int get_size_repo(struct Repo* repo);


int delete_from_repo(struct Repo* repo, int index);
int update_repo(struct Repo* repo, Medicine* elem,int index);



void testRepo();