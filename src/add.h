#pragma once

#include "traits.h"

template <typename T, typename OP1, typename OP2>
class Add{
public:
    explicit Add(const OP1& a, const OP2& b)
        : op1(a), op2(b) { }

    T operator[] (std::size_t idx) const{
        return op1[idx] + op2[idx];
    }

    // Potrebno za npr. Matrix = matrix + matrix
    T operator()(std::size_t row, std::size_t col) const{
        return op1(row,col) + op2(row, col);
    }

    std::size_t size() const {
        return op1.size() != 0 ? op1.size() : op2.size();
    }

    std::size_t rows() const {
        return op1.rows() != 0 ? op1.rows() : op2.columns();
    }

    std::size_t columns() const {
        return op1.columns() != 0 ? op1.columns() : op2.columns();
    }

    bool check_addr(T* addr) const{
        return op1.check_addr(addr) + op2.check_addr(addr);
    }


private:
    const OP1& op1;
    const OP2& op2;
};


