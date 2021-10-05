#pragma once

template <typename T, typename OP1, typename OP2>
class Mult{
public:
    explicit Mult(const OP1& a, const OP2& b)
        : op1(a), op2(b) {  }

    // sve ostalo
    T operator[] (std::size_t idx) const{
        return op1[idx] * op2[idx];
    }

    // Matrix = Scalar * Matrix
    T operator()(std::size_t row, std::size_t col) const{
        return op1(row, col) * op2(row, col);
    }

    std::size_t size() const {
        return op1.size() != 0 ? op1.size() : op2.size();
    }

    std::size_t rows() const {
        return op2.rows();
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
