#pragma once

#include <cstddef>
#include <cassert>
#include <iostream>
#include <initializer_list>

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

	using init_list = std::initializer_list<std::initializer_list<T> >;
    SDoubleArray(const init_list& list) : SDoubleArray(list.size(), (*list.begin()).size()) {
        auto current_row = list.begin();
        std::size_t idx = 0;
        while (current_row != list.end()) {
            auto current_col = (*current_row).begin();
            auto col_end = (*current_row).end();
            while (current_col != col_end) {
                storage[idx++] = (*current_col);
                ++current_col;
            }
            ++current_row;
        }
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
	
	for ( size_t i=0; i<a.rows(); ++i ) {
		for ( size_t j=0; j<b.columns (); ++j ) {
			for ( size_t k=0; k<b.columns(); ++k ) {
				result(i,k) += a(i,j) * b(j,k);
			}
		}
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
	SArray<T> result(a.rows());

	for (std::size_t k = 0; k < a.rows(); ++k) {
		for(std::size_t l = 0; l < a.columns(); ++l){
			result[k] += a(k,l) * b[l];
		}
	}
	return result;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const SDoubleArray<T>& mat) {
    out << '[';
    for (std::size_t idx = 0; idx < mat.rows(); ++idx) {
        for (std::size_t idy = 0; idy < mat.columns(); ++idy) {
            if (idx == mat.rows() - 1 && idy == mat.columns() - 1)
                continue;
            out << mat(idx, idy) << ", ";
        }
        if(idx != mat.rows()-1)
            out << "\n ";
    }
    if (mat.rows() + mat.columns() > 0) {
        out << mat(mat.rows()-1, mat.columns()-1);
    }
    out << "]\n";
    return out;
}