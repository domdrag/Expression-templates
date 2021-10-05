#pragma once

#include <cstddef>
#include <cassert>

// Greedy implementacija vektora
// Sluzi samo kao potencijalna mjera za usporedivanje performansi

template<typename T>
class SArray {
public:
	// create array with initial size
	explicit SArray(std::size_t s)
		: storage(new T[s]), storage_size(s)
	{
		init();
	}

	SArray(const std::initializer_list<T>& list) : SArray(list.size()) {
        auto begin = list.begin();
        std::size_t idx = 0;
        while (begin != list.end()) {
            storage[idx++] = *begin;
            ++begin;
        }
    }

	template <typename Device>
	SArray(std::size_t size, Device dev) : SArray(size) {
		copy(dev);
	}

	// copy constructor
	SArray(SArray<T> const& orig)
		: storage(new T[orig.size()]), storage_size(orig.size()) {
		copy(orig);
	}
	// destructor: free memory
	~SArray() {
		delete[] storage;
	}
	// assignment operator
	SArray<T>& operator= (SArray<T> const& orig) {
		if (&orig != this) {
			copy(orig);
		} return *this;
	}
	// return size
	std::size_t size() const {
		return storage_size;
	}
	// index operator for constants and variables
	T const& operator[] (std::size_t idx) const {
		return storage[idx];
	}
	T& operator[] (std::size_t idx) {
		return storage[idx];
	}
protected:
	// init values with default constructor
	void init() {
		for (std::size_t idx = 0; idx < size(); ++idx) {
			storage[idx] = T();
		}
	}
	//copy values of another array
	template <typename T1>
	void copy(T1& orig) {
		//assert(size() == orig.size());
		for (std::size_t idx = 0; idx < size(); ++idx) {
			storage[idx] = orig[idx];
		}
	}
private:
	T* storage; // storage of the elements
	std::size_t storage_size; // number of elements
};

template<typename T>
SArray<T> operator+ (SArray<T> const& a, SArray<T> const& b)
{
	assert(a.size() == b.size());
	SArray<T> result(a.size());
	for (std::size_t k = 0; k < a.size(); ++k) {
		result[k] = a[k] + b[k];
	}
	return result;
}
// multiplication of two SArrays
template<typename T>
SArray<T> operator* (SArray<T> const& a, SArray<T> const& b)
{
	assert(a.size() == b.size());
	SArray<T> result(a.size());
	for (std::size_t k = 0; k < a.size(); ++k) {
		result[k] = a[k] * b[k];
	}
	return result;
}

// multiplication of scalar and SArray
template<typename T>
SArray<T> operator* (T const& s, SArray<T> const& a)
{
	SArray<T> result(a.size());
	for (std::size_t k = 0; k < a.size(); ++k) {
		result[k] = s * a[k];
	}
	return result;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const SArray<T>& vect) {
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