#ifndef STAT
#define STAT
#include <iostream>
#include "Vector.h"
#include "TVector.h"
#include "time.h"

class Stat{
    private:
        double mean;
        double max;
        double min;
        double euclid;
        double sum;
        double tmean;
        double tmax;
        double tmin;
        double teuclid;
        double tsum;
        double n_thread;
        size_t size;
    public:
        Stat(size_t size){
            this->size = size;
        }

        ~Stat(){}

        void create_stats(int* threads, int len, const char* name){
            std::ofstream File(name);
            TVector<double> TVec(size);
            TVector<double> TVec_B(size);
            TVec.initialize_by_random(1, 10);
            TVec_B.initialize_by_random(1, 10);
            std::cout << "Loading: size of arr - "<< size<<"\n[>";
            for (int i=0; i < len; i++){
                std::cout << "==";
                if (threads[i] == 1){

                    Vector<double> Vec(size);
                    Vector<double> Vec_B(size);
                    Vec.initialize_by_random(1, 10);
                    Vec_B.initialize_by_random(1, 10);
                    //mean
                    {auto start_time = clock();
                    mean = Vec.mean();
                    auto end_time = clock();
                    tmean = (double)(end_time-start_time)/CLOCKS_PER_SEC;}                  
                    {auto start_time = clock();
                    sum = Vec.sum_elem();
                    auto end_time = clock();
                    tsum = (double)(end_time-start_time)/CLOCKS_PER_SEC;}
                    {auto start_time = clock();
                    euclid = Vec.euclid_metric(Vec_B);
                    auto end_time = clock();
                    teuclid = (double)(end_time-start_time)/CLOCKS_PER_SEC;}                  
                    {auto start_time = clock();
                    max = Vec.max().first;
                    auto end_time = clock();
                    tmax = (double)(end_time-start_time)/CLOCKS_PER_SEC;}                  
                    {auto start_time = clock();
                    min = Vec.min().first;
                    auto end_time = clock();
                    tmin = (double)(end_time-start_time)/CLOCKS_PER_SEC;}                  
                    File << threads[i] << " " << size << " ";
                    File << mean << " " << tmean << " ";
                    File << min << " " << tmin << " ";
                    File << max << " " << tmax << " ";
                    File << sum << " " << tsum << " ";
                    File << euclid << " " << teuclid << " ";
                    File << std::endl;
                }else{
                    auto min_rez = TVec.min(threads[i]);
                    min = min_rez.first.first;
                    tmin = min_rez.second;
                    auto max_rez = TVec.max(threads[i]);
                    max = max_rez.first.first;
                    tmax = max_rez.second;
                    auto sum_rez = TVec.sum_elem(threads[i]);
                    sum = sum_rez.first;
                    tsum = sum_rez.second;
                    auto mean_rez = TVec.mean(threads[i]);
                    mean = mean_rez.first;
                    tmean = mean_rez.second;
                    auto euclid_rez = TVec.euclid_metric(TVec_B, threads[i]);
                    euclid = euclid_rez.first;
                    teuclid = euclid_rez.second;
                    File << threads[i] << " " << size << " ";
                    File << mean << " " << tmean << " ";
                    File << min << " " << tmin << " ";
                    File << max << " " << tmax << " ";
                    File << sum << " " << tsum << " ";
                    File << euclid << " " << teuclid << " ";
                    File << std::endl;
                }
            }
            File.close();
            std::cout << ">]\nCompleate!!!\nChanges saved to "<<name;
        }                

};



#endif