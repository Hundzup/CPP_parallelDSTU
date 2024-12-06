#include <iostream>
#include "Vector.h"
#include <cstdlib>
#include <utility>

template<typename T>
Vector<T>::Vector(size_t n): n(n){
    data = new T[n];
    is_initialize = false;
}

template<typename T>
Vector<T>::~Vector(){
    delete[] data;
}

template<typename T>
void Vector<T>::initialize_by_const(T value){
    is_initialize = true;
    for(size_t i=0; i<n; i++){
        data[i] = value;
    }
}

// template<typename T>
// void Vector<T>::initialize_by_random(int start=0, int end=1){
//     // is_initialize = true;
//     // for(size_t i=0; i<n; i++){
//     //     data[i] = std::rand();
//     // }
//     std::cout << "ERROR!!!!!" << std::endl; 
// }

template<typename T>
T Vector<T>::sum_elem(){
    if (is_initialize == false){
        throw std::runtime_error("You have to initialize arry");
    }
    T sum=0;
    for(size_t i=0; i<n; i++){
        sum = sum + data[i];
    }
    return sum;
}

template<typename T>
T Vector<T>::mean(){
    if (is_initialize == false){
        throw std::runtime_error("You have to initialize arry");
    }
    T mean = 0;
    T count = n;
    for(size_t i=0; i<n; i++){
        mean = mean + data[i];
    }
    return mean/count;
}

template<typename T>
T Vector<T>::euclid_metric(){
    if (is_initialize == false){
        throw std::runtime_error("You have to initialize arry");
    }
    std::cout << "ERROR!!!" << std::endl;
}

template<typename T>
std::pair<T, size_t> Vector<T>::max(){
    if (is_initialize == false){
        throw std::runtime_error("You have to initialize arry");
    }
    T max = data[0];
    size_t ids = 0;
    for(size_t i=0; i<n; i++){
        if (data[i]>max){
            max=data[i];
            ids = i;
        }
    }
    return std::make_pair(max, ids);
}


template<typename T>
std::pair<T, size_t> Vector<T>::min(){
    if (is_initialize == false){
        throw std::runtime_error("You have to initialize arry");
    }
    T min = data[0];
    size_t ids = 0;
    for(size_t i=0; i<n; i++){
        if (data[i]<min){
            min=data[i];
            ids = i;
        }
    }
    return std::make_pair(min, ids);
}

template<typename T>
void Vector<T>::print(){
    for(size_t i = 0; i < n; i++){
        if (i == n-1){
            std::cout << data[i] << ".";
            continue;
        }
        std::cout << data[i] << ", ";
    }
    std::cout<< std::endl;
}