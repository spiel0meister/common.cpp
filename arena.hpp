#ifndef ARENA_HPP_
#define ARENA_HPP_
#include <cstddef>

struct Arena {
    void* data;
    size_t size;
    size_t capacity;

    Arena(size_t capacity_);
    ~Arena();

    void* pointer();
    template <typename T>
        T* alloc();
    template <typename T>
        T* copy(T& item);
    char* strcopy(char* str);
    char* sprintf(const char* fmt, ...);
    void reset();
};

#endif // ARENA_HPP_

#ifdef ARENA_IMPLEMENTATION
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cassert>

Arena::Arena(size_t capacity_) : capacity(capacity_), size(0) {
    data = malloc(capacity);
}

Arena::~Arena() {
    free(data);
}

void* Arena::pointer() {
    return (void*)((char*)data + size);
}

template <typename T>
T* Arena::alloc() {
    const size_t sizeof_t = sizeof(T);
    if (size + sizeof_t >= capacity) return nullptr;
    T* item = static_cast<T*>(this->pointer());
    size += sizeof_t;
    return item;
}

template <typename T>
T* Arena::copy(T& item) {
    T* copy_ = this->alloc<T>();
    memset(copy_, item, sizeof(T));
    return copy_;
}

char* Arena::strcopy(char* str) {
    return this->sprintf("%s", str);
}

char* Arena::sprintf(const char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    int n = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* str = static_cast<char*>(this->pointer());

    va_start(args, fmt);
    int n_ = vsnprintf(str, n, fmt, args);
    assert(n == n_);

    size += n_;
    va_end(args);

    return str;
}

void Arena::reset() {
    size = 0;
}

#endif // ARENA_IMPLEMENTATION
