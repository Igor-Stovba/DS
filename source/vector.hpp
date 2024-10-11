#pragma once

#include <cstddef>

template<typename T>
class Vector {
private:
    T* arr_;
    size_t sz_;
    size_t cap_;

public:
    class const_iterator {
    private:
        const T* ptr;
        iterator(T* ptr): ptr(ptr) {}
    public:
        // other methods
        const T& operator*() const {
            return *ptr;
        }
        const T* operator->() const {
            return ptr;
        }
    };

    class iterator {
    private:
        T* ptr;
        iterator(T *ptr): ptr(ptr) {}
    public:
        // other methods

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }
    };

    Vector(): arr_(nullptr), sz_(0), cap_(0) {}
    ~Vector() {
        for (size_t index = 0; index < sz_; ++index) {
            (arr_ + index)->~T();
        }
        delete[] reinterpret_cast<unsigned char*>(arr_);
    }
    size_t size() const noexcept {
        return sz_;
    }

    T& operator[](size_t index) {
        return arr_[index];
    }

    void reserve(size_t newcap) {
        if (newcap <= cap_) {
            return;
        }

        T* newarr = reinterpret_cast<T*>(new unsigned char[newcap * sizeof(T)]);
        
        size_t index = 0;
        try {
            for (; index < sz_; ++index) {
                new(newarr + index) T(arr_[index]);
            }
        } catch (...) {
            // invoke destructors 
            for (size_t prev_index = 0; prev_index < index; ++prev_index) {
                (newarr + prev_index)->~T();
            }
            delete [] reinterpret_cast<unsigned char*>(newarr);
            throw;
        }

        for (index = 0; index < sz_; ++index) {
            (arr_ + index)->~T();
        }
        delete [] reinterpret_cast<unsigned char*>(arr_);

        arr_ = newarr;
        cap_ = newcap;
    } 

    void push_back(const T& value) {
        if (sz_ == cap_) {
            reserve(cap_ == 0 ? 1 : 2 * cap_);
        }
        new(arr_ + sz_++) T(value);
    }

    iterator begin() {
        //
    }

    iterator end() {

    }

};

template <>
class Vector<bool> {
private:

public:

};