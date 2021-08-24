#pragma once

#include <type_traits>
#include <random>

template <typename T>
class Scalar;

template <typename T>
class Traits{
public:
    using ExprRef = const T&;
};

template <typename T>
class Traits<Scalar<T> >{
public:
    using ExprRef = Scalar<T>;
};

template <typename T>
using ExprRef = typename Traits<T>::ExprRef;

//////////////////////////////////

/*template <typename T>
class SVector;

template <typename T>
class MatTraits {
public:
    using ExprRef = const T&;
};

template <typename T>
class MatTraits<Scalar<T> > {
public:
    using ExprRef = Scalar<T>;
};

template <typename T>
class MatTraits<SVector<T> > {
public:
    using ExprRef = SVector<T>;
};

template <typename T>
using ExprRefMat = typename MatTraits<T>::ExprRef; */

///////////////////////////////////////////////

template <bool value, typename T>
struct uniform_type {
    using Type = typename std::uniform_int_distribution<T>;
};

template <typename T>
struct uniform_type<false, T> {
    using Type = typename std::uniform_real_distribution<T>;
};

template <typename T>
using uniform_type_distribution = typename uniform_type<std::is_integral<T>::value, T>::Type;