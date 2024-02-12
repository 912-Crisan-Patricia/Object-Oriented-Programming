#pragma once
#include <string>

class trenchCoat {
private:
	std::string _size;
	std::string _colour;
	int _price = 0;
	int _quantity = 0;
	std::string _photograph;

public:
	//default constructor
	trenchCoat() = default;

	//constructor
	trenchCoat(std::string size, std::string colour, int price, int quantity, std::string photograph);

	//copy constructor
	trenchCoat(const trenchCoat& t);

	//assignment operator
	//:return: copy of the trench Coat
	trenchCoat& operator=(const trenchCoat& t);

	//destructor
	~trenchCoat();

	//getter function for size
	std::string size() const;

	//getter function for colour
	std::string colour() const;

	//getter function for price
	int price() const;

	//getter function for quantity
	int quantity() const;

	//getter function for photograph
	std::string photograph() const;

	//setter function for size
	void setSize(std::string size);

	//setter function for colour
	void setColour(std::string colour);

	//setter function for price
	void setPrice(int price);

	//setter function for quantity
	void setQuantity(int quantity);

	//setter function for photograph
	void setPhotograph(std::string photograph);

	//equality function
	//:return: true if the  id's are equal (size, colour and photograph), false otherwise
	static bool equal(const trenchCoat& t, const std::string size, const std::string colour, const std::string);

	bool operator==(const trenchCoat& t) const;

	//convertion to string function
	//:return: string representation of the trench coat
	std::string toString() const;
};
