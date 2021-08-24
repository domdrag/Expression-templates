#pragma once

#include <cassert>
#include <initializer_list>

template <typename T>
class SMatrix {
public:
    explicit SMatrix(std::size_t row, std::size_t col)
        : storage(new T[row*col]), mRows(row), mColumns(col) {
        init();
    }

    SMatrix(const SMatrix& orig) : SMatrix(orig.rows(), orig.columns()) {
        copy(orig);
    }

    using init_list = std::initializer_list<std::initializer_list<T> >;
    SMatrix(const init_list& list) : SMatrix(list.size(), (*list.begin()).size()) {
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

    template <typename Device>
    SMatrix(std::size_t row, std::size_t col, Device dev) : SMatrix(row, col) {
        copy(dev);
    }

    SMatrix(std::size_t row, std::size_t col, T value) : SMatrix(row, col) {
        init(value);
    }

    const T& operator()(std::size_t row, std::size_t col) const {
        return storage[row * mColumns + col];
    }

    T& operator() (std::size_t row, std::size_t col) {
        return storage[row * mColumns + col];
    }

    const T& operator[] (std::size_t idx) const {
        return storage[idx];
    }

    T& operator[] (std::size_t idx) {
        return storage[idx];
    }

    const std::size_t& rows() const { return mRows; }

    const std::size_t& columns() const { return mColumns; }

    T* addr() const {
        return storage;
    }

    bool check_addr(T* addr) const{
        if(addr == storage)
            return true;
        return false;
    }

protected:
    void init(T value = T());
    template <typename T1>
    void copy(T1& orig);

private:
    T* storage;
    std::size_t mRows;
    std::size_t mColumns;
};

template <typename T>
void SMatrix<T>::init(T value) {
    for (std::size_t idx = 0; idx < mRows * mColumns; ++idx) {
        storage[idx] = value;
    }
}

template <typename T> template <typename T1>
void SMatrix<T>::copy(T1& orig) {
    for (std::size_t idx = 0; idx < mRows * mColumns; ++idx) {
        storage[idx] = orig[idx];
    }
}