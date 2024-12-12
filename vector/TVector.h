#ifndef VECTOR_T
#define VECTOR_T
#include <cstddef>
#include <utility>
#include "Vector.h"
#include <mutex>
#include <thread>
#include <cmath>
#include "time.h"

template<typename T>
class TVector :public Vector<T>{
    private:
        mutable std::mutex mtx;
        size_t n;
        T* data;;
        bool is_initialize;
    public:
        TVector(size_t n) : Vector<T>(n){}

        ~TVector(){}

        using Vector<T>::initialize_by_const;

        using Vector<T>::initialize_by_random;

        using Vector<T>::export2file;

        using Vector<T>::importfromfile;

        using Vector<T>::operator();

        using Vector<T>::print;

        using Vector<T>::getN;

        using Vector<T>::getIs_initialize;

        std::pair<T, double> sum_elem(int n_thread){
                int count_lenght = ((*this).getN()/(double)n_thread);
                Vector<std::thread> threads(n_thread);
                T global_sum = 0;

                auto sum_thred = [this, &global_sum](size_t start, size_t end){
                    T local_sum  = 0;
                    for (size_t i=start; i < end; i++){
                        local_sum = local_sum + this->operator()(i);
                    }
                    
                    std::lock_guard<std::mutex> lock(this->mtx);
                    global_sum = global_sum + local_sum;
                };

                auto start_time = clock();
                for (int i = 0; i < n_thread; i++){
                    if (i != n_thread-1){
                        threads(i) = std::thread(sum_thred, i*count_lenght, (i+1)*count_lenght);
                    }else{
                        threads(i) = std::thread(sum_thred, i*count_lenght, (*this).getN());
                    }
                }

                for (int i = 0; i < n_thread; i++){
                    threads(i).join();
                }
                auto end_time = clock();
                auto duration = (end_time-start_time);

                return std::make_pair(global_sum, (double)duration/CLOCKS_PER_SEC);
        }

        std::pair<T, double> euclid_metric(const Vector<T>& other, int n_thread) const{
            if (this->getIs_initialize() == false){
                throw std::runtime_error("You have to initialize arry");
            }
            if (this->getN() != other.getN()){
                throw std::invalid_argument("Need the same size of vectors");
            }
            int count_lenght = this->getN()/(double)n_thread;
            Vector<std::thread> threads(n_thread);
            T rezult = 0;

            auto euclid_thread = [this, &rezult, &other](size_t start, size_t end){
                T local_rezult = 0;
                for (size_t i=start; i < end; i++){
                    local_rezult += sqrt(pow(this->operator()(i) - other.operator()(i), 2));
                } 
                std::lock_guard<std::mutex> lock(this->mtx);
                rezult += local_rezult;
            };

            auto start_time = clock();
            for (int i=0; i < n_thread; i++){
                if (i != n_thread-1){
                    threads(i) = std::thread(euclid_thread, i*count_lenght, (i+1)*count_lenght);
                }else{
                    threads(i) = std::thread(euclid_thread, i*count_lenght, (*this).getN());
                }
            }

            for (int i=0; i < n_thread; i++){
                threads(i).join();
            }

            auto end_time = clock();
            auto duration = end_time - start_time;
            return std::make_pair(rezult, (double)duration/CLOCKS_PER_SEC);
        }

        std::pair<T, double> mean(int n_thread){
            if (this->getIs_initialize() == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T mean = 0;
            T count = this->getN();
            int count_lenght = this->getN()/(double)n_thread;
            Vector<std::thread> threads(n_thread);

            auto mean_thread = [this, &mean](size_t start, size_t end){
                T local_mean = 0;
                for (size_t i = start; i < end; i++){
                    local_mean += this->operator()(i);
                }
                std::lock_guard<std::mutex> lock(this->mtx);
                mean += local_mean;
            };
            
            auto start_time = clock();
            for (int i = 0; i < n_thread; i++){
                if (i != n_thread-1){
                    threads(i) = std::thread(mean_thread, i*count_lenght, (i+1)*count_lenght);
                }else{
                    threads(i) = std::thread(mean_thread, i*count_lenght, this->getN());
                }
            }
            for (int i = 0; i < n_thread; i++){
                threads(i).join();
            }
            auto end_time = clock();
            auto duration = end_time - start_time;
            return std::make_pair(mean/count, (double)duration/CLOCKS_PER_SEC);
        }

        std::pair<T, double> multiply(const Vector<T>& other, int n_thread) const{
            if (this->getN() != other.getN()){
                throw std::invalid_argument("Need the same size of vectors");
            }
            if (this->getIs_initialize() == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T rezult = 0;
            Vector<std::thread> threads(n_thread);
            int count_lenght = this->getN()/(double)n_thread;

            auto multiply_thread = [this, &rezult, &other](size_t start, size_t end){
                T local_rezult = 0;
                for (size_t i = start; i < end; i++){
                    local_rezult += this->operator()(i) * other.operator()(i);
                }
                std::lock_guard<std::mutex> lock(this->mtx);
                rezult += local_rezult;
            };
            
            auto start_time = clock();
            for (int i = 0; i < n_thread; i++){
                if (i != n_thread-1){
                    threads(i) = std::thread(multiply_thread, i*count_lenght, (i+1)*count_lenght);
                }else{
                    threads(i) = std::thread(multiply_thread, i*count_lenght, (*this).getN());
                }
            }
            for (int i = 0; i < n_thread; i++){
                threads(i).join();
            }
            auto end_time = clock();
            auto duration = end_time - start_time;
            return std::make_pair(rezult, (double)duration/CLOCKS_PER_SEC);
        }

        std::pair<std::pair<T, size_t>, double> max(int n_thread){
            if (this->getIs_initialize() == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T max = this->operator()(i);
            size_t idx = 0;
            int count_lenght = this->getN()/(double)n_thread;
            Vector<std::thread> threads(n_thread);

            auto max_thread = [this, &max, &idx](size_t start, size_t end){
                T local_max = this->operator()(start);
                size_t local_idx = start;
                for (size_t i = start; i < end; i++){
                    if (this->operator()(i) > local_max){
                        local_max = this->operator()(i);
                        local_idx = i;
                    }
                }
                std::lock_guard<std::mutex> lock(this->mtx);
                if (local_max > max){
                    max = local_max;
                    idx = local_idx;
                }
            };
            
            auto start_time = clock();
            for (int i = 0; i < n_thread; i++){
                if (i != n_thread-1){
                    threads(i) = std::thread(max_thread, i*count_lenght, (i+1)*count_lenght);
                }else{
                    threads(i) = std::thread(max_thread, i*count_lenght, (*this).getN());
                }
            }
            for (int i = 0; i < n_thread; i++){
                threads(i).join();
            }
            auto end_time = clock();
            auto duration = end_time - start_time;
            return std::make_pair(std::make_pair(max, idx), (double)duration/CLOCKS_PER_SEC);
        }

        std::pair<std::pair<T, size_t>, double> min(int n_thread){
            if (this->getIs_initialize() == false){
                throw std::runtime_error("You have to initialize arry");
            }
            T min = this->operator()(0);
            size_t idx = 0;
            int count_lenght = this->getN()/(double)n_thread;
            Vector<std::thread> threads(n_thread);

            auto min_thread = [this, &min, &idx](size_t start, size_t end){
                T local_min = this->operator()(start);
                size_t local_idx = start;
                for (size_t i = start; i < end; i++){
                    if (this->operator()(i) < local_min){
                        local_min = this->operator()(i);
                        local_idx = i;
                    }
                }
                std::lock_guard<std::mutex> lock(this->mtx);
                if (local_min < min){
                    min = local_min;
                    idx = local_idx;
                }
            };
            
            auto start_time = clock();
            for (int i = 0; i < n_thread; i++){
                if (i != n_thread-1){
                    threads(i) = std::thread(min_thread, i*count_lenght, (i+1)*count_lenght);
                }else{
                    threads(i) = std::thread(min_thread, i*count_lenght, (*this).getN());
                }
            }
            for (int i = 0; i < n_thread; i++){
                threads(i).join();
            }
            auto end_time = clock();
            auto duration = end_time - start_time;
            return std::make_pair(std::make_pair(min, idx), (double)duration/CLOCKS_PER_SEC);
        }
};


#endif