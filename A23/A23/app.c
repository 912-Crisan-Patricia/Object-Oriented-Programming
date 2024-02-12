#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "domain.h"
#include "dynarray.h"
#include "repo.h"
#include "controller.h"

int main()
{
	testDomain();
	testDynArray();
	testRepo();
	testController();

	struct UI* ui = ui_init();


	/*char* c;
	c = (char*)malloc(100);*/
	run(ui);
	ui_destr(ui);

	_CrtDumpMemoryLeaks();
	return 0;
}