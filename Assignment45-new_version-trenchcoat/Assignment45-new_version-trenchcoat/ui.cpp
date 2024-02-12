#include <iostream>
#include <string>
#include "ui.h"
#include "controller.h"
#include "dynamicVector.h"


UI::UI() : _controller{ Controller() } {}

Controller UI::controller() const
{
	return this->_controller;
}

void UI::addEntries() {
	this->_controller.addEntries();
}

void UI::startMenu() {
	std::cout << "1. Administrator mode\n";
	std::cout << "2. User mode\n";
	std::cout << "0. Exit\n";
}

bool UI::validOption(std::string option) {
	for (char c : option) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

void UI::adminMenu() {
	std::cout << "1. Add a new trench Coat\n";
	std::cout << "2. Delete a trench Coat\n";
	std::cout << "3. Update a trench Coat\n";
	std::cout << "4. List all trench Coats\n";
	std::cout << "0. Exit\n";
}
void UI::adminMode() {
	bool running = true;
	std::string optionString;
	Controller controller = this->controller();
	while (running) {
		adminMenu();
		std::cin >> optionString;
		if (validOption(optionString)) {
			int option = std::stoi(optionString);
			std::string size, colour, price, quantity, photograph, newSize, newColour, newPrice, newQuantity, newPhotograph;
			repository repo;
			switch (option) {
			case 1:
				std::cout << "Size: ";
				std::cin >> size;
				std::cout << "Colour: ";
				std::cin >> colour;
				std::cout << "Price: ";
				std::cin >> price;
				std::cout << "Quantity: ";
				std::cin >> quantity;
				std::cout << "Photograph: ";
				std::cin >> photograph;
				if (controller.addTrenchCoat(size, colour, price, quantity, photograph))
					std::cout << "Trench Coat added successfully\n";
				else
					std::cout << "Failed to add trench coat\n";
				break;
			case 2:
				std::cout << "Size: ";
				std::cin >> size;
				std::cout << "Colour: ";
				std::cin >> colour;
				std::cout << "Photograph: ";
				std::cin >> photograph;
				if (controller.removeTrenchCoat(size, colour, photograph))
					std::cout << "Trench Coat removed successfully\n";
				else
					std::cout << "Failed to remove trench coat\n";
				break;
			case 3:
				std::cout << "Size: ";
				std::cin >> size;
				std::cout << "Colour: ";
				std::cin >> colour;
				std::cout << "Photograph: ";
				std::cin >> photograph;
				std::cout << "New size: ";
				std::cin >> newSize;
				std::cout << "New colour: ";
				std::cin >> newColour;
				std::cout << "New price: ";
				std::cin >> newPrice;
				std::cout << "New quantity: ";
				std::cin >> newQuantity;
				std::cout << "New photograph: ";
				std::cin >> newPhotograph;
				if (controller.updateTrenchCoat(size, colour, photograph, newSize, newColour, newPrice, newQuantity, newPhotograph))
					std::cout << "Trench Coat updated successfully\n";
				else
					std::cout << "Failed to update trench coat\n";
				break;
			case 4:
				repo = controller.repo();
				for (int i = 0; i < repo.length(); i++)
					std::cout << repo[i].toString() << "\n";
				break;
			case 0:
				running = false;
				break;
			default:
				std::cout << "Invalid option\n";
				break;
			}
		}
		else
			std::cout << "Invalid option\n";
	}
}

void UI::userMenu() {
	std::cout << "1. Filter trench coats\n";
	std::cout << "2. See shopping basket\n";
	std::cout << "0. Exit\n";
}

void UI::userMode() {
	bool running = true, buying = true;
	std::string optionString, filter, optionString2;
	Controller controller = this->controller();
	repository filteredCoats, shoppingCart;
	int price = 0, option2;
	bool ok;
	trenchCoat coat;
	while (running) {
		userMenu();
		std::cin >> optionString;
		if (validOption(optionString)) {
			int option = std::stoi(optionString);
			switch (option) {
			case 1:
				std::cout << "Filter: ";
				std::cin.get();
				std::getline(std::cin, filter);
				price = 0;
				while (buying) {
					filteredCoats = controller.filterBySize(filter);
					for (int i = 0; i < filteredCoats.length(); i++) {
						std::cout << "Current value in shopping cart: " << price << "\n";
						std::cout << filteredCoats[i].toString() << "\n";
						std::cout << "1. Add to shopping cart\n";
						std::cout << "2. Next\n";
						std::cout << "0. Exit\n";
						std::cin >> optionString2;
						if (!validOption(optionString2))
							option2 = 2;
						else
							option2 = std::stoi(optionString2);
						if (option2 == 0) {
							buying = false;
							break;
						}
						else if (option2 == 1) {
							price += filteredCoats[i].price();
							coat = trenchCoat{ filteredCoats[i].size(), filteredCoats[i].colour(), filteredCoats[i].price(), 1, filteredCoats[i].photograph() };
							ok = shoppingCart.addTrenchCoat(coat);
							if (!ok) {
								for (i = 0; i < shoppingCart.length(); i++)
									if (shoppingCart[i] == coat) {
										coat = trenchCoat{ shoppingCart[i].size(), shoppingCart[i].colour(), shoppingCart[i].price(), shoppingCart[i].quantity() + 1, shoppingCart[i].photograph() };
										shoppingCart.updateTrenchCoat(shoppingCart[i].size(), shoppingCart[i].colour(), shoppingCart[i].photograph(), coat);
										break;
									}
							}
							controller.updateTrenchCoat(filteredCoats[i].size(), filteredCoats[i].colour(), filteredCoats[i].photograph(), filteredCoats[i].size(), filteredCoats[i].colour(), std::to_string(filteredCoats[i].price()), std::to_string(filteredCoats[i].quantity() - 1), filteredCoats[i].photograph());
						}
					}
				}
			case 2:
				for (int i = 0; i < shoppingCart.length(); i++)
					std::cout << shoppingCart[i].toString();
				std::cout << "Current value in shopping cart: " << price << '\n';
				break;
			case 0:
				running = false;
				break;
			default:
				std::cout << "Invalid option\n";
				break;
			}
		}
		else
			std::cout << "Invalid option\n";
	}

}

void UI::startApp() {
	UI ui{};
	ui.addEntries();
	std::string modeOptionString;
	bool running = true;
	while (running) {
		startMenu();
		std::cin >> modeOptionString;
		if (validOption(modeOptionString)) {
			int modeOption = std::stoi(modeOptionString);
			switch (modeOption) {
			case 1:
				ui.adminMode();
				break;
			case 2:
				ui.userMode();
				break;
			case 0:
				running = false;
				break;
			default:
				std::cout << "Invalid option\n";
				break;
			}
		}
		else
			std::cout << "Invalid option\n";
	}
}
