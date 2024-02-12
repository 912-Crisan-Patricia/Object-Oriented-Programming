#include "trenchCoat.h"


trenchCoat::trenchCoat(std::string size, std::string colour, int price, int quantity, std::string photograph) :
	_size{ size }, _colour{ colour }, _price{ price }, _quantity{ quantity }, _photograph{ photograph } {}

trenchCoat::trenchCoat(const trenchCoat& t) :
	_size{ t._size }, _colour{ t._colour }, _price{ t._price }, _quantity{ t._quantity }, _photograph{ t._photograph } {}

trenchCoat& trenchCoat::operator=(const trenchCoat& t) {
	this->_size = t._size;
	this->_colour = t._colour;
	this->_price = t._price;
	this->_quantity = t._quantity;
	this->_photograph = t._photograph;
	return *this;
}

trenchCoat::~trenchCoat() {}

std::string trenchCoat::size() const {
	return this->_size;
}

std::string trenchCoat::colour() const {
	return this->_colour;
}

int trenchCoat::price() const {
	return this->_price;
}

int trenchCoat::quantity() const {
	return this->_quantity;
}

std::string trenchCoat::photograph() const {
	return this->_photograph;
}

void trenchCoat::setSize(std::string size) {
	this->_size = size;
}

void trenchCoat::setColour(std::string colour) {
	this->_colour = colour;
}

void trenchCoat::setPrice(int price) {
	this->_price = price;
}

void trenchCoat::setQuantity(int quantity) {
	this->_quantity = quantity;
}

void trenchCoat::setPhotograph(std::string photograph) {
	this->_photograph = photograph;
}

bool trenchCoat::equal(const trenchCoat& t, const std::string size, const std::string colour, const std::string photograph) {
	return (t.size() == size && t.colour() == colour && t.photograph() == photograph);
}

bool trenchCoat::operator==(const trenchCoat& t) const
{
	return trenchCoat::equal(*this, t._size, t._colour, t._photograph);
}

std::string trenchCoat::toString() const
{
	std::string str = "";
	str += "Size: ";
	str += this->_size;
	str += " || Colour: ";
	str += this->_colour;
	str += " || Price: ";
	str += std::to_string(this->_price);
	str += " || Quantity: ";
	str += std::to_string(this->_quantity);
	str += " || Photograph: ";
	str += this->_photograph;
	str += "\n";
	return str;
}
