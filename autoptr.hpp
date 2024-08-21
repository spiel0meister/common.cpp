#ifndef AUTOPTR_H_
#define AUTOPTR_H_

template <typename T>
struct AutoPtr {
    T* data;
    
    AutoPtr();
    AutoPtr(T* data_);
    ~AutoPtr();

    AutoPtr(const AutoPtr& other);

    T operator=(T thing);
    T operator->();
    T operator*();
};

#endif // AUTOPTR_H_
#ifdef AUTOPTR_IMPLEMENTATION
template <typename T>
AutoPtr<T>::AutoPtr() : data(new T) {}

template <typename T>
AutoPtr<T>::AutoPtr(T* data_) : data(data_) {}

template <typename T>
AutoPtr<T>::~AutoPtr() {
    delete data;
}

template <typename T>
T AutoPtr<T>::operator=(T thing) { 
    return (*data = thing);
}

template <typename T>
T AutoPtr<T>::operator->() {
    return *data;
}

template <typename T>
T AutoPtr<T>::operator*() {
    return *data;
}

template <typename T>
AutoPtr<T>::AutoPtr(const AutoPtr<T>& other) : data(new T(*other.data)) {}
#endif // AUTOPTR_IMPLEMENTATION
