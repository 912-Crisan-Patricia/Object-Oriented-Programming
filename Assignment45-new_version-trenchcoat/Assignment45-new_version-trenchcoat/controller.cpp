#include "controller.h"
#include <string>

bool Controller::validInput(std::string input) {
	for (char c : input) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}
Controller::Controller() : _repo{ repository() } {}

repository Controller::repo() const { return this->_repo; }

void Controller::addEntries() {
	this->_repo.addEntries();
}

bool Controller::addTrenchCoat(std::string size, std::string colour, std::string price, std::string quantity, std::string photograph) {
	if (!validInput(price) || !validInput(quantity)) {
		return false;
	}
	int priceInt = std::stoi(price);
	int quantityInt = std::stoi(quantity);
	return this->_repo.addTrenchCoat(trenchCoat{ size, colour, priceInt, quantityInt, photograph });
}

bool Controller::removeTrenchCoat(std::string size, std::string colour, std::string photograph) {
	return this->_repo.removeTrenchCoat(size, colour, photograph);
}

bool Controller::updateTrenchCoat(std::string size, std::string colour, std::string photograph, std::string newSize, std::string newColour, std::string newPrice, std::string newQuantity, std::string newPhotograph) {
	if (!validInput(newPrice) || !validInput(newQuantity)) {
		return false;
	}
	int newPriceInt = std::stoi(newPrice);
	int newQuantityInt = std::stoi(newQuantity);
	return this->_repo.updateTrenchCoat(size, colour, photograph, trenchCoat{ newSize, newColour, newPriceInt, newQuantityInt, newPhotograph });
}

repository Controller::filterBySize(std::string size)
{
	if (size == "")
		return this->repo();
	repository filteredRepo, repo = this->repo();
	for (int i = 0; i < repo.length(); i++) {
		if (repo[i].size() == size)
			filteredRepo.addTrenchCoat(repo[i]);
	}
	return filteredRepo;
}
