#include "signallib.h"

SignalLib::SignalLib() {

}
// Function to check if a number is a power of two
bool SignalLib::IsPowerOfTwo(size_t n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Function to compute the next power of two greater than or equal to n
size_t SignalLib::NextPowerOfTwo(size_t n) {
    if (IsPowerOfTwo(n)) return n;
    size_t power = 1;
    while (power < n) power <<= 1;
    return power;
}
void SignalLib::FFT(std::vector<std::complex<float>>& x){
    const size_t N = x.size();

    // Check if N is a power of 2
    if (!IsPowerOfTwo(N)) {
        std::cerr << "Error: FFT input size must be a power of 2.\n";
        exit(EXIT_FAILURE);
    }

    // Bit-reversal permutation for improve butterfly computation efficiency
    size_t j = 0;
    for (size_t i = 0; i < N; ++i) {
        if (i < j) {
            std::swap(x[i], x[j]);
        }
        size_t m = N >> 1;
        while (m >= 1 && j >= m) {
            j -= m;
            m >>= 1;
        }
        if (m >= 1) {
            j += m;
        }
    }

    // FFT computation using Cooley-Turkey radix-2 algorithm
    for (size_t s = 1; s <= static_cast<size_t>(std::log2(N)); ++s) {
        size_t m = 1 << s;           // m = 2^s
        size_t m2 = m >> 1;          // m2 = m/2
        float theta = -2.0f * PI / m;
        std::complex<float> wm(std::cos(theta), std::sin(theta));

        for (size_t k = 0; k < N; k += m) {
            std::complex<float> w(1.0f, 0.0f);
            for (size_t j = 0; j < m2; ++j) {
                std::complex<float> t = w * x[k + j + m2];
                std::complex<float> u = x[k + j];
                x[k + j] = u + t;
                x[k + j + m2] = u - t;
                w *= wm;
            }
        }
    }

}
void SignalLib::PrepareAndFFT(std::vector<std::complex<float>>& x){
    const size_t N = x.size();

    if (!IsPowerOfTwo(N)) {
        size_t nextN = NextPowerOfTwo(N);
        size_t dif = nextN - N;

        for (size_t i = 0; i < dif; ++i) { //Fill remaining with zero padding for Cooley–Tukey adaptation
            x.emplace_back(0.f,0.f);
        }
    }

    FFT(x);

}
