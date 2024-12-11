#include <iostream>
#include "Vector.h"
#include <cstdlib>
#include <utility>
#include <cmath>
#include <random>
#include <fstream>
#include <string>

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

template<typename T>
void Vector<T>::initialize_by_random(T start, T end){
    is_initialize = true;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(start, end);
    for(size_t i=0; i<n; i++){
        data[i] = (T)distrib(gen);
    }
}

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
T Vector<T>::euclid_metric(const Vector<T>& other) const{
    if (is_initialize == false){
        throw std::runtime_error("You have to initialize arry");
    }
    if (n!=other.n){
        throw std::invalid_argument("Need the same size of vectors");
    }
    T rezult = 0;
    for(size_t i=0; i < n; i++){
        rezult += sqrt(pow(data[i] - other(i), 2));
    }
    return rezult;
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

template<typename T>
T Vector<T>::multiply(const Vector<T>& other) const{
    if (n != other.n){
        throw std::invalid_argument("Need the same size of vectors");
    }
    if (is_initialize == false){
        throw std::runtime_error("You have to initialize arry");
    }
    T rezult = 0;
    for(size_t i = 0; i < n; i++){
        rezult += data[i] * other(i);
    }
    return rezult;
}

template<typename T>
const T& Vector<T>::operator()(size_t i) const{
    return data[i];
}

template<typename T>
void Vector<T>::export2file(const char* name){
    std::ofstream outFile(name);
    outFile << n << std::endl;
    for (size_t i=0; i<n; i++){
        outFile << data[i] << " ";
    }
    outFile.close();
}

template<typename T>
void Vector<T>::importfromfile(const char* name){
    std::ifstream inputFile(name);
    size_t n_tmp;
    inputFile >> n_tmp;
    if (n_tmp != n){
        throw std::invalid_argument("Not the same size of arrays");
    }

    for (size_t i=0; i<n; i++){
        inputFile >> data[i];
    }

    inputFile.close();
}
