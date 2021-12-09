#pragma once

#include <cassert>
#include <cstddef>
#include <algorithm>


#include "svector.h"
#include "add.h"
#include "mult.h"
#include "scalar.h"

template <typename T, typename Rep = SVector<T>, bool Mat_Mult = false>
class Vector{
public:
    /// Potrebno da korisnik nema pristup adresi vektora u memoriji
    template <typename, typename, bool> friend class Vector; 

    explicit Vector(std::size_t s) :
        expr_rep(s), mSize(s) {  }

    explicit Vector(const Rep& rb) :
        expr_rep(rb), mSize(rb.size()) { }

    Vector(const std::initializer_list<T>& list)
        : expr_rep(list), mSize(list.size()) {  }

    /// Sluzi za kreiranje vektora random vrijednostima (koristeci klasu Random)
    template <typename Device>
    explicit Vector(std::size_t size, Device dev) : 
        expr_rep(size, dev), mSize(size) {
    }

    /// Sluzi za kreiranje vektora istom vrijednoscu
    explicit Vector(std::size_t size, T value) : /// Sluzi za kreiranje vektora istom vrijednoscu
        expr_rep(size, value), mSize(size) {
    }


    Vector& operator= (const Vector& b){
        for (std::size_t idx = 0; idx < mSize; ++idx){
            expr_rep[idx] = b[idx];
        }
        return *this;
    }

    template <typename T2, typename Rep2>
    Vector& operator= (const Vector<T2, Rep2, false>& b) {
        for (std::size_t idx = 0; idx < mSize; ++idx) {
            expr_rep[idx] = b[idx];
        }

        return *this;
    }

    template <typename T2, typename Rep2>
    Vector& operator= (const Vector<T2, Rep2, true>& b){
        // Ako se vektor na lijevoj strani pridruzivanja pojavljuje u mnozenju sa matricom na desnoj strani
        // tada je potrebno kreirati temp. objekt
        if(b.check_addr(addr())){
            T* temp = new T[mSize];
            for (std::size_t idx = 0; idx < mSize; ++idx) {
                temp[idx] = b[idx];
            }
            for (std::size_t idx = 0; idx < mSize; ++idx) {
                expr_rep[idx] = temp[idx];
            }
            delete[] temp;
            return *this;
        }

        for (std::size_t idx = 0; idx < mSize; ++idx) {
            expr_rep[idx] = b[idx];
        }

        return *this;
    }


    decltype(auto) operator[] (std::size_t idx) const{
        return expr_rep[idx];
    }

    T& operator[] (std::size_t idx){
        return expr_rep[idx];
    }

    std::size_t size() const {
        return mSize;
    }

    const Rep& rep() const{
        return expr_rep;
    }

    Rep& rep() {
        return expr_rep;
    }

    bool check_addr(T* addr) const {
        return expr_rep.check_addr(addr);
    }


private:
    Rep expr_rep;
    std::size_t mSize;

     T* addr() const {
         return expr_rep.addr();
     }
};

template <typename T, typename Rep>
std::ostream& operator<< (std::ostream& out, const Vector<T,Rep>& vect) {
    out << '[';
    for (std::size_t idx = 0; idx < vect.size() - 1; ++idx) {
        out << vect[idx] << ", ";
    }
    if (vect.size() > 0) {
        out << vect[vect.size() - 1];
    }
    out << "]\n";
    return out;
}


