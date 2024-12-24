#ifndef OVECTOR_H
#define OVECTOR_H
#include "Vector.h"
#include <omp.h>
#include <cstddef>
#include "time.h"

template<typename T>
class OVector: public Vector<T>{
    private:
        size_t n;
        T* data;
        bool is_initialize = false;
    public:
        OVector(size_t n) : Vector<T>(n){}
        
        ~OVector(){
            delete[] data;
        }

        using Vector<T>::initialize_by_const;

        using Vector<T>::print;

        using Vector<T>::getIs_initialize;

        using Vector<T>::operator();

        using Vector<T>::getN;

        std::pair<T, double> sum_elem(int n_thread = -1){
            T rezult = 0;
            auto start = clock();
            if (n_thread == -1){
                #pragma omp parallel for
                for (size_t i = 0; i < getN(); i++){
                    rezult += operator()(i);
                }
            }else{
                omp_set_num_threads(n_thread);
                #pragma omp parallel for
                for (size_t i = 0; i < getN(); i++){
                    rezult += operator()(i);
                }
            }
            auto end = clock();
            return std::make_pair(rezult, (double)(end - start)/CLOCKS_PER_SEC);
        }

        std::pair<T, double> mean(int n_thread=-1){
            T mean = 0;
            auto start = clock();
            if (n_thread == -1){
                T local_mean = 0;
                #pragma omp parallel for
                for (size_t i = 0; i < getN(); i++){
                    local_mean += operator()(i);
                }

                #pragma omp atomic
                mean += local_mean;
            }else{
                omp_set_num_threads(n_thread);   
                T local_mean = 0;
                #pragma omp parallel for
                for (size_t i = 0; i < getN(); i++){
                    local_mean += operator()(i);
                }

                #pragma omp atomic
                mean += local_mean;
            }
            mean = mean/getN();
            auto end = clock();
            return std::make_pair(mean, (double)(end-start)/CLOCKS_PER_SEC);
        }

};


#endif