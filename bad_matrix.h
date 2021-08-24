#pragma once

#include <cstddef>
#include <cassert>
#include <iostream>

#include "bad_vector.h"

// Greedy implementacija vektora
// Sluzi samo kao potencijalna mjera za usporedivanje performansi

template<typename T>
class SDoubleArray {
public:
	// create array with initial size
	explicit SDoubleArray(std::size_t row, std::size_t col)
		: storage(new T[row*col]), mRows(row), mColumns(col)
	{
		init();
	}

	template <typename Device>
	SDoubleArray(std::size_t row, std::size_t col, Device dev) : SDoubleArray(row, col) {
		copy(dev);
	}

	// copy constructor
	SDoubleArray(SDoubleArray<T> const& orig)
		: storage(new T[orig.rows() * orig.columns()]),
		 mRows(orig.rows()), mColumns(orig.columns())
	 {
		copy(orig);
	}
	// destructor: free memory
	~SDoubleArray() {
		delete[] storage;
	}
	// assignment operator
	SDoubleArray<T>& operator= (SDoubleArray<T> const& orig) {
		if (&orig != this) {
			copy(orig);
		} return *this;
	}
	// index operator for constants and variables
	const T& operator() (std::size_t row, std::size_t col) const {
		return storage[row * mColumns + col];
	}
	T& operator() (std::size_t row, std::size_t col)  {
		return storage[row * mColumns + col];
	}

	std::size_t columns() const {
		return mColumns;
	}

	std::size_t rows() const {
		return mRows;
	}

	const T& operator[] (std::size_t idx) const {
        return storage[idx];
    }

    T& operator[] (std::size_t idx) {
        return storage[idx];
    }
protected:
	// init values with default constructor
	void init() {
		for (std::size_t idx = 0; idx < rows()*columns(); ++idx) {
			storage[idx] = T();
		}
	}
	//copy values of another array
	template <typename T1>
	void copy(T1& orig) {
		for (std::size_t idx = 0; idx < rows()*columns(); ++idx) {
			storage[idx] = orig[idx];
		}
	}

private:
    T* storage;
    std::size_t mRows;
    std::size_t mColumns;
};

template<typename T>
SDoubleArray<T> operator+ (SDoubleArray<T> const& a, SDoubleArray<T> const& b)
{
	SDoubleArray<T> result(a.rows(), b.columns());
	for (std::size_t k = 0; k < a.rows()*a.columns(); ++k) {
		result[k] = a[k] + b[k];
	}
	return result;
}
// multiplication of two SArrays
template<typename T>
SDoubleArray<T> operator* (SDoubleArray<T> const& a, SDoubleArray<T> const& b)
{
	SDoubleArray<T> result(a.rows(), b.columns());
	for (std::size_t k = 0; k < a.rows()*a.columns(); ++k) {
		result[k] = a[k] * b[k];
	}
	return result;
}

// multiplication of scalar and SArray
template<typename T>
SDoubleArray<T> operator* (T const& s, SDoubleArray<T> const& a)
{
	SDoubleArray<T> result(a.rows(), a.columns());
	for (std::size_t k = 0; k < a.rows()*a.columns(); ++k) {
		result[k] = s * a[k];
	}
	return result;
}

template<typename T>
SArray<T> operator* (SDoubleArray<T> const& a, SArray<T> const& b)
{
	SArray<T> result(b.size());
	for (std::size_t k = 0; k < a.rows(); ++k) {
		for(std::size_t l = 0; l < a.columns(); ++l){
			result[k] += a(k,l) * a[l];
		}
	}
	return result;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const SDoubleArray<T>& vect) {
	out << '[';
	for (std::size_t idx = 0; idx < vect.size() - 1; ++idx) {
		out << vect[idx] << ", ";
	}
	if (vect.size() > 0) {
		out << vect[vect.size() - 1];
	}
	out << ']';
	return out;
}