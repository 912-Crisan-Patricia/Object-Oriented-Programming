#pragma once
#include "dynamicVector.h"
#include "trenchCoat.h"
#include <string>

class repository {
private:
	dynamicVector<trenchCoat> _trenchCoats;

public:
	//constructor
	repository();

	//copy constructor
	repository(const repository& r);

	//destructor
	~repository();

	//creates 10 random entries in the repo
	void addEntries();

	//getter function for length
	int length() const;

	//getter operator for trench coat
	//:return: element on the position given
	//throws an error if index is out of array bounds
	trenchCoat& operator[](int index) const;

	//adds a trench coat to the repository
	//:param: t - trench coat
	//:return: true if the trench coat was added, false otherwise
	bool addTrenchCoat(trenchCoat t);

	//removes a trench coat from the repository
	//:param: t - trench coat
	//:return: true if the trench coat was removed, false otherwise
	bool removeTrenchCoat(const std::string size, const std::string colour, const std::string photograph);

	//updates a trench coat from the repository
	//:param: t - trench coat
	//:return: true if the trench coat was updated, false otherwise
	bool updateTrenchCoat(const std::string size, const std::string colour, const std::string photograph, trenchCoat t);
};


