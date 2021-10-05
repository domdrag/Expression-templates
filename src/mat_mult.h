#pragma once

#include "traits.h"

template <typename T, typename OP1, typename OP2>
class Mat_Mult {
public:
    explicit Mat_Mult(const OP1& a, const OP2& b)
        : op1(a), op2(b) { }
    
    //// Potrebno samo za Vect = Mat * Vect slucaj
    T operator[] (std::size_t idx) const { 
        T sum = 0;
        for (std::size_t idy = 0; idy < op2.rows(); ++idy) {
            sum += op1(idx,idy) * op2[idy];
        }
        return sum;
    }

    std::size_t size() const {
        return op2.size();
    }

    std::size_t rows() const {
        return op1.rows() != 0 ? op1.rows() : op2.rows();
    }

    std::size_t columns() const {
        return op2.columns();
    }

    bool check_addr(T* addr) const{
        return op1.check_addr(addr) + op2.check_addr(addr);
    }

private:
    ExprRef<OP1> op1;
    ExprRef<OP2> op2;
};
