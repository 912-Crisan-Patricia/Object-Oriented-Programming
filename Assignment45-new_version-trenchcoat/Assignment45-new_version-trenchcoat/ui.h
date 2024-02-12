#pragma once
#include <string>
#include "repository.h"
#include "controller.h"

class UI {
private:
	Controller _controller;
public:

	//constructor
	UI();

	//getter for the controller
	Controller controller() const;

	//generator of entries
	void addEntries();

	//menu 
	static void startMenu();

	//user input validation 
	static bool validOption(std::string option);

	//menu for admin mode
	static void adminMenu();

	//starts the admin mode ui
	void adminMode();

	//menu for user mode
	static void userMenu();

	//starts the user mode ui
	void userMode();

	//starts app
	static void startApp();
};

