#pragma once

#include <cassert>
#include <initializer_list>

template <typename T>
class SVector{
public:
    explicit SVector(std::size_t s)
     : storage(new T[s]), storage_size(s){
        init();
     }

    SVector(const SVector& orig) : SVector(orig.size()) {
        copy(orig);
     }

    SVector(const std::initializer_list<T>& list) : SVector(list.size()) {
        auto begin = list.begin();
        std::size_t idx = 0;
        while (begin != list.end()) {
            storage[idx++] = *begin;
            ++begin;
        }
    }

    template <typename Device>
    SVector(std::size_t size, Device dev) : SVector(size) {
        copy(dev);
    }
    
    SVector(std::size_t size, T value) : SVector(size) {
        init(value);
    }

    /*SVector<T>& operator= (const SVector<T>& orig) {
        std::cout << "Treba" << std::endl;
        if( this != &orig ){
            copy(orig);
        }
        return *this;
    }*/

    const T& operator[] (std::size_t idx) const{
        return storage[idx];
    }

    T& operator[] (std::size_t idx){
        return storage[idx];
    }

    std::size_t size() const { return storage_size; }

    std::size_t rows() const {
        return storage_size;
    }

    std::size_t columns() const {
        return 1;
    }

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
    std::size_t storage_size;
};

template <typename T>
void SVector<T>::init(T value){
    for(std::size_t idx = 0; idx < storage_size; ++idx){
        storage[idx] = value;
    }
}

template <typename T> template <typename T1>
void SVector<T>::copy(T1& orig){
    //assert(size() == orig.size());
    for(std::size_t idx = 0; idx < storage_size; ++idx){
        storage[idx] = orig[idx];
    }
}

