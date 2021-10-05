#pragma once

#include <typeinfo>
#include <cassert>
#include <cstddef>
#include <vector>

#include "smatrix.h"
#include "add.h"
#include "mult.h"
#include "scalar.h"
#include "mat_mult.h"

template <typename T, typename Rep = SMatrix<T>>
class Matrix {
public:

    explicit Matrix(std::size_t row, std::size_t col)
        : expr_rep(row,col), mRows(row), mColumns(col) {  }


    explicit Matrix(const Rep& rb) 
        : expr_rep(rb), mRows(rb.rows()), mColumns(rb.columns()) { }

    using init_list = std::initializer_list<std::initializer_list<T> >;
    Matrix(const init_list& list)
        : expr_rep(list), mRows(list.size()),
        mColumns((*list.begin()).size()) {  }

    template <typename Device>
    explicit Matrix(std::size_t row, std::size_t col, Device dev) 
        : expr_rep(row, col, dev), mRows(row), mColumns(col) {
    }

    explicit Matrix(std::size_t row, std::size_t col, T value) 
        : expr_rep(row, col, value), mRows(row), mColumns(col) {
    }

    template <typename T2, typename Rep2>
    Matrix(const Matrix<T2, Rep2>& b) 
        : expr_rep(b.rows(),b.columns()), mRows(b.rows()), mColumns(b.columns())  {
        for (std::size_t idx = 0; idx < mRows; ++idx) {
            for (std::size_t idy = 0; idy < mColumns; ++idy) {
                expr_rep(idx, idy) = b(idx, idy);
            }
        }  
    }

    Matrix& operator= (const Matrix& b) {
        for (std::size_t idx = 0; idx < mRows; ++idx) {
            for (std::size_t idy = 0; idy < mColumns; ++idy) {
                expr_rep(idx, idy) = b(idx, idy);
            }
        }
        return *this;
    }

    template <typename T2, typename Rep2>
    Matrix& operator= (const Matrix<T2, Rep2>& b) {
        for (std::size_t idx = 0; idx < mRows; ++idx) {
            for (std::size_t idy = 0; idy < mColumns; ++idy) {
                expr_rep(idx, idy) = b(idx, idy);
            } 
        }

        return *this;
    }

    std::size_t rows() const {
        return mRows;
    }

    std::size_t columns() const {
        return mColumns;
    }

    decltype(auto) operator() (std::size_t row, std::size_t col) const {
        return expr_rep(row,col);
    }

    T& operator() (std::size_t row, std::size_t col) {
        return expr_rep(row, col);
    }

    const Rep& rep() const {
        return expr_rep;
    }

    Rep& rep() {
        return expr_rep;
    }

private:
    Rep expr_rep;
    std::size_t mRows;
    std::size_t mColumns;

};


template <typename T, typename Rep>
std::ostream& operator<< (std::ostream& out, const Matrix<T, Rep>& mat) {
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



