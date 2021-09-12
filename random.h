#pragma once

#include <random>

#include "traits.h"

// sluzi sa inicijalizaciju random brojevima iz nekog intervala
template <typename T>
class Random {
public:
    Random(T a, T b); // interval [a,b]
    Random(Random const& rhs);
    Random& operator=(Random const& rhs) = delete;
    T operator[](std::size_t);
private:
    std::random_device rd;
    std::default_random_engine r_engine;
    uniform_type_distribution<T> dist;
};

template <typename T>
Random<T>::Random(T a, T b) : dist(a, b), r_engine(rd()) {}

template <typename T>
Random<T>::Random(Random const& rhs) {
    r_engine.seed(rd());
    dist = rhs.dist;
}

template <typename T>
T Random<T>::operator[] (std::size_t) {
    return dist(r_engine);
}