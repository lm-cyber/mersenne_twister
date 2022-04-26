//
// Created by void on 26.04.22.
//

#include "test_fourier.h"
void  fft(double *prng_value,size_t length) {
    std::vector<std::complex<double>> out;

    std::vector<std::complex<double>> in;
    for (size_t i = 0; i < length ; ++i) {
        out.push_back(prng_value[i]);
        in.push_back((double)i);
    }
    fftw_plan result = fftw_plan_dft_1d(length,(fftw_complex*) &in[0],(fftw_complex*) &out[0],FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(result);
    fftw_destroy_plan(result);

    // выводим в файл результат преобразования Фурье (должна получиться Дельта-функция)
    std::ofstream out_file("speсtr.txt");
    for(size_t i=0; i<length; ++i)
    {
        out_file<<prng_value[i]<<std::endl;
    }


}