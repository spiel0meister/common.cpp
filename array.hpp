#ifndef ARRAY_HPP_
#define ARRAY_HPP_
#include <cstddef>

template <typename T>
struct Array {
    T* data;
    size_t count;
    size_t capacity;

    Array();
    Array(size_t capacity_);
    ~Array();

    T operator[](int index) const;
    void push(T item);
    void push_many(T* items, size_t count);
    void maybe_resize(size_t new_items_count);
    T pop();
};


#endif // ARRAY_HPP_

#ifdef ARRAY_IMPLEMENTATION

#include <cstdio>
#include <cstdlib>
#include <cstring>

template <typename T>
void Array<T>::maybe_resize(size_t new_items_count) {
    if (count + new_items_count >= capacity) {
        if (capacity == 0) capacity = 16;
        while (count + new_items_count >= capacity) capacity *= 2;
        T* new_data = new T[capacity];
        memcpy(new_data, data, count * sizeof(T));
        delete[] data;
        data = new_data;
    }
}

template <typename T>
Array<T>::Array() : capacity(16), count(0) {
    data = new T[capacity];
}

template <typename T>
Array<T>::Array(size_t capacity_) : capacity(capacity_), count(0) {
    data = new T[capacity];
}

template <typename T>
Array<T>::~Array() {
    delete[] data;
}

template <typename T>
T Array<T>::operator[](int index) const {
    return data[index];
}

template <typename T>
void Array<T>::push(T item) {
    maybe_resize(1);
    data[count++] = item;
}

template <typename T>
void Array<T>::push_many(T* items, size_t count) {
    maybe_resize(count);
    memcpy(data + this->count, items, count * sizeof(T));
    this->count += count;
}

template <typename T>
T Array<T>::pop() {
    return data[--count];
}

#endif // ARRAY_IMPLEMENTATION

