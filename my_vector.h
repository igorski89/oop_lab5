/*
 *  my_vector.h
 *  cpp_vector_iter
 *
 *  Created by Igor Evsukov on 19.05.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <cstddef>
#include <iterator>
//using namespace std;
template<class T> class MyVector {
public:
    typedef T value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef std::size_t size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    
protected:
//    T* p_begin;
//    T* p_end;
    
    T* data;
    int capacity;
    int count;
    void realloc();
    
    
public:    
    MyVector();
    MyVector(int init_capacity);
    MyVector(MyVector<T>& vector);
    
    ~MyVector();
    
    int getCount() const;
    int getCapacity() const;
    bool isFull() const;	
    bool isEmpty() const;	
    
    void add(const T& elem);
    void insert(int i, const T& elem);
    void insert(const T& t, const T& elem);
    
    void removeAt(int i);
    void remove(const T& elem);
    void removeAll();
        
//    T getAt(int i);
    
    const T& operator[](int index) const;
    T& operator[](int index);
    
    iterator begin() { 
        return data;
    //return p_begin; 
    };
    iterator end() { 
        //return p_end; 
        return (data+count);
    };
    
};

template <class T> MyVector<T>::MyVector() {
    count = 0;
    capacity = 10;
    data = new T[10];
}

template <class T> MyVector<T>::MyVector(int init_capacity) {
    count = 0;
    capacity = init_capacity;
    data = new T[capacity];
}

template <class T> MyVector<T>::MyVector(MyVector<T>& vector) {
    count = vector.getCount();
    capacity = vector.getCapacity();
    data = new T[capacity];
    for(int i = 0; i < count; i++)
        data[i] = vector[i];
}

template <class T> MyVector<T>::~MyVector() {
    delete[] data; 
}

template <class T> void MyVector<T>::realloc() {
    capacity *= 2;
    if (capacity == 0) capacity = 2;
    T* new_data = new T[capacity];
    for (int i = 0; i < count; i++)
        new_data[i] = data[i];
    delete[] data;
    data = new_data;
}

template <class T> int MyVector<T>::getCapacity() const {
    return capacity;
}

template <class T> int MyVector<T>::getCount() const {
    return count;
}

template <class T> bool MyVector<T>::isFull() const {
    return count == capacity;
}

template <class T> bool MyVector<T>::isEmpty() const {
    return count == 0;
}

template <class T> void MyVector<T>::add(const T& elem) {
    if (count == capacity) realloc();
    data[count++] = elem;
}

template <class T> void MyVector<T>::insert(int i, const T& elem) {
    if( (i < 0) || (i >= count))
        throw "index out of range";
    if (count == capacity) realloc();
    count++;
    T temp = data[i];
    T temp2;
    data[i] = elem;
    for(int j = i+1; j < count; j++) {
        temp2 = data[j];
        data[j] = temp;
        temp = temp2;	
    }
}

template <class T> void MyVector<T>::insert(const T& t, const T& elem) {
//    int i = Find(t);
    int i = 0;
    for (i=0; i < count; i++)
        if (data[i] == t)
            break;
    
    if( i == -1)
        return;
    if (count == capacity) realloc();
    count++;
    T temp = data[i];
    T temp2;
    data[i] = elem;
    for(int j = i+1; j < count; j++) {
        temp2 = data[j];
        data[j] = temp;
        temp = temp2;	
    }
}

template <class T> void MyVector<T>::removeAt(int i) {
    if ( (i < 0) || (i >= count) ) return;
    count--;
    for(int j = i; j < count; j++)
        data[j] = data[j+1];
}

//template <class T> T MyVector<T>::getAt(int i) {
//    if ( (i < 0) || (i >= count) ) throw "index out of range";
//    return data[i];
//}

template <class T> const T& MyVector<T>::operator[](int index) const { 
    if ( (index < 0) || (index >= count) )
        throw "index out of range";
    return data[index];
}

template <class T> T& MyVector<T>::operator[](int index) { 
    if ( (index < 0) || (index >= count) )
        throw "index out of range";
    return data[index];
}


#endif
