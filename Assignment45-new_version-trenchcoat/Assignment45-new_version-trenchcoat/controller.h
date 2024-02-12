#pragma once
#include <string>
#include "repository.h"

class Controller {
private:
	repository _repo;
public:

	//validation method for integer fields
	static bool validInput(std::string input);

	//constructor
	Controller();

	//getter for the repository
	repository repo() const;

	//creates 10 random entries in the repo
	void addEntries();

	//adds a trench coat to the repository
	bool addTrenchCoat(std::string size, std::string colour, std::string price, std::string quantity, std::string photograph);

	//removes a trench coat identified by size, colour and photograph from the repository
	bool removeTrenchCoat(std::string size, std::string colour, std::string photograph);

	//updates a trench coat identifided by size, colour and photograph with the new size, colour, price, quantity and photograph
	bool updateTrenchCoat(std::string size, std::string colour, std::string photograph, std::string newSize, std::string newColour, std::string newPrice, std::string newQuantity, std::string newPhotograph);

	//returns a filtered repo containing all trench coats with a given size
	repository filterBySize(std::string size);
};

