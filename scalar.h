#pragma once

template <typename T>
class Scalar{
public:
    explicit Scalar(T const & v): s(v) {}

    const T& operator[] (std::size_t) const{
        return s;
    }

    const T& operator() (std::size_t row, std::size_t col) const{
        return s;
    }

    std::size_t size() const{
        return 0;
    }

    std::size_t rows() const {
        return 0;
    }

    std::size_t columns() const {
        return 0;
    }

    bool check_addr(T* addr) const{
        return false;
    }

private:
    const T& s;
};
