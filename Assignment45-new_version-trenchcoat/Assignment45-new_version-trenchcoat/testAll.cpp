#include "testAll.h"
#include "dynamicVector.h"
#include "trenchCoat.h"
#include "repository.h"
#include "controller.h"

#include <string>
#include <assert.h>
#include <exception>

void testDynamicVector() {
	dynamicVector<int> numberVector{};
	dynamicVector<std::string> stringVector{};

	//test constructor, len and cap
	assert(numberVector.length() == 0 && stringVector.length() == 0);
	assert(numberVector.capacity() == 100 && stringVector.capacity() == 100);

	//test [] operator
	try {
		numberVector[2];
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}

	//test copy constructor
	dynamicVector<int> copy{ numberVector };
	assert(copy.length() == numberVector.length() && copy.capacity() == numberVector.capacity());
	numberVector.add(1);
	assert(copy.length() != numberVector.length());

	//test assignment operator
	dynamicVector<int> assign;
	assign = numberVector;
	assert(assign.length() == numberVector.length() && assign.capacity() == numberVector.capacity());
	numberVector.add(2);
	assert(assign.length() != numberVector.length());

	//test destructor
	dynamicVector<int>* destructor = new dynamicVector<int>();
	delete destructor;

	//test []
	numberVector.add(3);
	assert(numberVector[0] == 1 && numberVector[1] == 2 && numberVector[2] == 3);
	try {
		numberVector[3];
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}

	//test add
	assert(numberVector.add(4) == true);
	assert(numberVector.length() == 4 && numberVector.capacity() == 100);
	assert(numberVector.add(4) == false);
	assert(numberVector.length() == 4 && numberVector.capacity() == 100);

	dynamicVector<int> numberVector2{}, numberVector3{};
	for (int i = 1; i < 100; i++)
		numberVector2.add(i);
	assert(numberVector2.length() == 99 && numberVector2.capacity() == 100);
	numberVector3 = numberVector2;
	numberVector2.add(100);
	assert(numberVector2.length() == 100 && numberVector2.capacity() == 200);
	for (int i = 0; i < 99; i++)
		assert(numberVector2[i] == numberVector3[i]);

	//test remove
	assert(numberVector.remove(0) == true);
	assert(numberVector.length() == 3 && numberVector.capacity() == 100);
	assert(numberVector.remove(3) == false);
	assert(numberVector.length() == 3 && numberVector.capacity() == 100);

	//test search
	assert(numberVector.search(2) == 0);
	assert(numberVector.search(3) == 1);
	assert(numberVector.search(4) == 2);
	assert(numberVector.search(5) == -1);

	//test update
	assert(numberVector.update(0, 5) == true);
	assert(numberVector[0] == 5);
	assert(numberVector.update(3, 5) == false);
	stringVector.add("test");
	assert(stringVector.update(0, "test2") == true);
}

void testTrenchCoat() {
	//test constructor and getters
	trenchCoat coat0{};
	assert(coat0.size() == "" && coat0.colour() == "" && coat0.price() == 0 && coat0.quantity() == 0 && coat0.photograph() == "");
	trenchCoat coat1{ "test", "test", 1, 1, "https://test" };
	assert(coat1.size() == "test" && coat1.colour() == "test" && coat1.price() == 1 && coat1.quantity() == 1 && coat1.photograph() == "https://test");

	//test copy constructor
	trenchCoat coat2{ coat1 };
	assert(coat2.size() == "test" && coat2.colour() == "test" && coat2.price() == 1 && coat2.quantity() == 1 && coat2.photograph() == "https://test");

	//test assignment operator
	trenchCoat coat3{ "test2", "test2", 2, 2, "https://test2" };
	coat3 = coat1;
	assert(coat3.size() == "test" && coat3.colour() == "test" && coat3.price() == 1 && coat3.quantity() == 1 && coat3.photograph() == "https://test");

	//test setters
	coat1.setSize("test2");
	coat1.setColour("test2");
	coat1.setPrice(2);
	coat1.setQuantity(2);
	coat1.setPhotograph("https://test2");
	assert(coat1.size() == "test2" && coat1.colour() == "test2" && coat1.price() == 2 && coat1.quantity() == 2 && coat1.photograph() == "https://test2");

	//test equality
	assert(trenchCoat::equal(coat2, coat3.size(), coat3.colour(), coat3.photograph()));
	assert(!trenchCoat::equal(coat1, coat2.size(), coat2.colour(), coat2.photograph()));

	//test to string
	assert(coat1.toString() == "Size: test2 || Colour: test2 || Price: 2 || Quantity: 2 || Photograph: https://test2\n");
}

void testRepository() {

	//test constructor and length
	repository repo{};
	assert(repo.length() == 0);

	//test copy constructor
	trenchCoat t1{ "test", "test", 1, 1, "https://test" };
	repo.addTrenchCoat(t1);
	repository repo2{ repo };
	assert(repo.length() == 1);
	assert(repo2.length() == 1);

	//test [] operator
	assert(repo[0] == t1);
	try {
		repo[2];
		assert(false);
	}
	catch (std::exception& e) {
		assert(true);
	}

	//test add
	trenchCoat t2{ "test2", "test2", 2, 2, "https://test2" };
	trenchCoat t3{ "test3", "test3", 3, 3, "https://test3" };
	assert(repo.addTrenchCoat(t2) == true);
	assert(repo.addTrenchCoat(t3) == true);
	assert(repo.addTrenchCoat(t1) == false);
	assert(repo.length() == 3);

	//test remove
	assert(repo.removeTrenchCoat(t2.size(), t2.colour(), t2.photograph()) == true);
	assert(repo.removeTrenchCoat(t1.size(), t1.colour(), t1.photograph()) == true);
	assert(repo.length() == 1);
	assert(repo.removeTrenchCoat(t2.size(), t2.colour(), t2.photograph()) == false);

	//test update
	assert(repo.updateTrenchCoat(t3.size(), t3.colour(), t3.photograph(), t1) == true);
	assert(repo.updateTrenchCoat(t1.size(), t1.colour(), t1.photograph(), t2) == true);
	assert(repo.updateTrenchCoat(t3.size(), t3.colour(), t3.photograph(), t1) == false);

	//test add entries
	repository repo0{};
	repo0.addEntries();
	assert(repo0.length() == 10);

}

void testController() {
	//test constructor and add entries
	Controller ctrl{};
	repository repo{};
	repo = ctrl.repo();
	assert(repo.length() == 0);

	ctrl.addEntries();
	repo = ctrl.repo();
	assert(repo.length() == 10);

	//test add trench coat
	assert(ctrl.addTrenchCoat("fdgd", "fdg", "12", "23", "ggdfgd") == true);
	repo = ctrl.repo();
	assert(repo.length() == 11);
	assert(ctrl.addTrenchCoat("fdgd", "fdg", "12gf", "23", "ggdfgd") == false);
	repo = ctrl.repo();
	assert(repo.length() == 11);

	//test remove trench coat
	assert(ctrl.removeTrenchCoat("fdgd", "fdg", "ggdfgd") == true);
	repo = ctrl.repo();
	assert(repo.length() == 10);
	assert(ctrl.removeTrenchCoat("fdgd", "fdg", "ggdfgd") == false);
	repo = ctrl.repo();
	assert(repo.length() == 10);

	//test update trench coat
	assert(ctrl.addTrenchCoat("fdgd", "fdg", "12", "23", "ggdfgd") == true);
	repo = ctrl.repo();
	assert(repo.length() == 11);
	assert(ctrl.updateTrenchCoat("fdgd", "fdg", "ggdfgd", "fdgd23", "fd2g", "1222", "2333", "ggdfgd") == true);
	repo = ctrl.repo();
	assert(repo.length() == 11);
	assert(ctrl.updateTrenchCoat("fdgd23", "fd2g", "ggdfgd", "fdgdsd23", "fddss2g", "122dsfs", "2333", "ggdfgd") == false);

	//test valid input static method
	assert(Controller::validInput("12") == true);
	assert(Controller::validInput("12.2") == false);

	//test filter
	ctrl.addTrenchCoat("fdgd23", "dfsd", "12", "23", "ggdfgd");
	repo = ctrl.filterBySize("fdgd23");
	assert(repo.length() == 2);
	repo = ctrl.filterBySize("");
	assert(repo.length() == 12);
}

void testEverything() {
	testDynamicVector();
	testTrenchCoat();
	testRepository();
	testController();
}
