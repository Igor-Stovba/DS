#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cstddef>
#include <iterator>

template<typename T>
class Vector {
private:
    T* arr_;
    size_t sz_;
    size_t cap_;

    template <bool IsConst>
    class base_iterator {
    public:
        using value_type = T;
        using pointer_type = std::conditional<IsConst, const T*, T*>::type;
        using reference_type = std::conditional<IsConst, const T&, T&>::type;
        using iterator_category = std::contiguous_iterator_tag;
    private:
        pointer_type * ptr;
        iterator(T *ptr): ptr(ptr) {}
    public:
        // req: CopyConstructable
        iterator(const base_iterator& it) = default;

        // req: CopyAssignable
        iterator& operator=(const iterator& it) = default;

        // req: dereferenceable
        reference_type & operator*() const {
            return *ptr;
        }

        pointer_type* operator->() const {
            return ptr;
        }

        base_iterator& operator++() {
            ptr++;
            return *this;
        }
        base_iterator operator++(int) {
            base_iterator copy = *this;
            ptr++;
            return copy;
        }
        base_iterator& operator--() {
            ptr--;
            return *this;
        }
        base_iterator operator--(int) {
            base_iterator copy = *this;
            ptr--;
            return copy;
        }
    };
public:
    using iterator = base_iterator<false>;
    using const_iterator = base_iterator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

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
        return {arr_};
    }

    const_iterator begin() const {
        return {arr_};
    }

    iterator end() {
        return {arr_ + sz_};
    }

    const_iterator end() const {
        return {arr_ + sz_};
    }

    const_iterator cbegin() const {
        return {arr_};
    }

    const_iterator cend() const {
        return {arr_ + sz_};
    }
};

template <>
class Vector<bool> {
private:

public:

};

#endif