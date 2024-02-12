#pragma once
#include <exception>
#include <algorithm>
#include "trenchCoat.h"

template <typename T>
class dynamicVector {

private:
	T* _elems;
	int _length, _capacity;

public:
	//constructor
	dynamicVector();

	//copy constructor
	dynamicVector(const dynamicVector& v);

	//assignment operator
	//:return: copy of the dynamicVector
	dynamicVector<T>& operator=(const dynamicVector& v);

	//destructor
	~dynamicVector();
	;
	//getter function for array length
	int length() const;

	//getter function for array capacity
	int capacity() const;

	//getter operator
	//:return: element on the position given
	//throws an error if index is out of array bounds
	T& operator[](int index) const;

	//adds an element of Type t to the dynamic array
	//if array capacity is reached, this method extends the array
	//:return: True if add was successful, False if element already exists
	bool add(T element);

	//removes element from position index from the array
	//throws error if index is out of array bounds
	bool remove(int index);

	//searches for the existance of an element in the array
	//:return: element position if found, -1 otherwise
	int search(T element);

	//changes element at position index with given element
	//:return: True if update was successful, False if not
	bool update(int index, T element);
};

template <typename T>
dynamicVector<T>::dynamicVector() : _length{ 0 }, _capacity{ 100 } {
	this->_elems = new T[_capacity];
}

template <typename T>
dynamicVector<T>::dynamicVector(const dynamicVector& v) : _length{ v._length }, _capacity{ v._capacity } {
	this->_elems = new T[_capacity];
	std::copy(v._elems, v._elems + v._length, this->_elems);
}

template <typename T>
dynamicVector<T>& dynamicVector<T>::operator=(const dynamicVector& v) {
	this->_length = v._length;
	this->_capacity = v._capacity;
	delete[] this->_elems;
	this->_elems = new T[_capacity];
	std::copy(v._elems, v._elems + v._length, this->_elems);
	return *this;
}

template <typename T>
dynamicVector<T>::~dynamicVector() {
	delete[] this->_elems;
}

template <typename T>
int dynamicVector<T>::length() const { return this->_length; };

template <typename T>
int dynamicVector<T>::capacity() const { return this->_capacity; };

template <typename T>
T& dynamicVector<T>::operator[](int index) const {
	if (index < 0 || index >= this->_length)
		throw std::exception();
	return this->_elems[index];
};

template <typename T>
bool dynamicVector<T>::add(T element) {
	for (int i = 0; i < this->_length; i++)
		if (this->_elems[i] == element)
			return false;
	this->_elems[this->_length] = element;
	this->_length++;
	if (this->_length == this->_capacity) {
		T* newElems = new T[this->_capacity * 2];
		std::copy(this->_elems, this->_elems + this->_length, newElems);
		delete[] this->_elems;
		this->_elems = newElems;
		this->_capacity *= 2;
	}
	return true;
}

template <typename T>
bool dynamicVector<T>::remove(int index) {
	if (index < 0 || index >= this->_length)
		return false;
	std::copy(this->_elems + index + 1, this->_elems + this->_length, this->_elems + index);
	this->_length--;
	return true;
}

template <typename T>
int dynamicVector<T>::search(T element) {
	for (int i = 0; i < this->_length; i++)
		if (this->_elems[i] == element)
			return i;
	return -1;
}

template <typename T>
bool dynamicVector<T>::update(int index, T element) {
	if (index < 0 || index >= this->_length)
		return false;
	this->_elems[index] = element;
	return true;
}
