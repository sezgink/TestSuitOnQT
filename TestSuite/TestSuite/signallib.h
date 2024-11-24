#pragma once

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

#define PI 3.1416

class SignalLib
{

    bool IsPowerOfTwo(size_t n);

    // Calculate the next power of two greater than or equal to n
    size_t NextPowerOfTwo(size_t n);

public:
    SignalLib();
    void FFT(std::vector<std::complex<float>>& x);
    void PrepareAndFFT(std::vector<std::complex<float>>& x); //For non power of 2 input prepare data

};
