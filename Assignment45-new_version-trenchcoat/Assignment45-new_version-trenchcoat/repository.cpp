#include "repository.h"
#include "trenchCoat.h"
#include <string>
#include <random>

repository::repository() : _trenchCoats{ dynamicVector<trenchCoat>() } {}

repository::repository(const repository& r) : _trenchCoats{ r._trenchCoats } {}

repository::~repository() {}

void repository::addEntries() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> random(1, 5);
	std::uniform_int_distribution<> randomNr(10, 120);
	std::string sizes[] = { "XS", "S", "M", "L", "XL", "XXL" };
	std::string colors[] = { "Purple", "Green", "Blue", "Orange", "Red", "White" };
	int i = 0;
	while (i < 10) {
		trenchCoat t{ sizes[random(gen) - 1], colors[random(gen) - 1], randomNr(gen), randomNr(gen), "https://itemlinknumber" + std::to_string(i + 1) };
		if (this->_trenchCoats.add(t))
			i++;
	}
}

int repository::length() const
{
	return this->_trenchCoats.length();
}

trenchCoat& repository::operator[](int index) const
{
	try {
		return this->_trenchCoats[index];
	}
	catch (std::exception& e) {
		throw e;
	}
}

bool repository::addTrenchCoat(trenchCoat t)
{
	for (int i = 0; i < this->_trenchCoats.length(); i++)
		if (trenchCoat::equal(t, this->_trenchCoats[i].size(), this->_trenchCoats[i].colour(), this->_trenchCoats[i].photograph()))
			return false;
	this->_trenchCoats.add(t);
	return true;
}

bool repository::removeTrenchCoat(const std::string size, const std::string colour, const std::string photograph)
{
	for (int i = 0; i < this->_trenchCoats.length(); i++)
		if (trenchCoat::equal(this->_trenchCoats[i], size, colour, photograph)) {
			this->_trenchCoats.remove(i);
			return true;
		}
	return false;
}

bool repository::updateTrenchCoat(const std::string size, const std::string colour, const std::string photograph, trenchCoat t)
{
	for (int i = 0; i < this->_trenchCoats.length(); i++)
		if (trenchCoat::equal(this->_trenchCoats[i], size, colour, photograph)) {
			this->_trenchCoats[i] = t;
			return true;
		}
	return false;
}