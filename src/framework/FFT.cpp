#include "FFT.h"
#include <cmath>

namespace Hunchback::Framework {

static constexpr double kPi = 3.14159265358979323846;
static constexpr int    kLog = 9; // log2(kBufferSize)

FFT::FFT() {
    for (unsigned int i = 0; i < kBufferSize; ++i) {
        unsigned int val = i;
        unsigned int reversed = 0;
        for (int b = 0; b < kLog; ++b) {
            reversed = (reversed << 1) | (val & 1);
            val >>= 1;
        }
        _bitReverse[i] = reversed;
    }
    for (int i = 0; i < kBufferSize / 2; ++i) {
        double angle = 2.0 * kPi * i / kBufferSize;
        _cosTable[i] = static_cast<float>(std::cos(angle));
        _sinTable[i] = static_cast<float>(std::sin(angle));
    }
}

void FFT::prepare(const short* input) {
    for (int i = 0; i < kBufferSize; ++i) {
        _real[i] = static_cast<float>(input[_bitReverse[i]]);
        _imag[i] = 0.0f;
    }
}

void FFT::calculate() {
    int exchanges = 1;
    int factfact  = kBufferSize / 2;
    for (int i = kLog; i != 0; --i) {
        for (int j = 0; j < exchanges; ++j) {
            float fact_real = _cosTable[j * factfact];
            float fact_imag = _sinTable[j * factfact];
            for (int k = j; k < kBufferSize; k += exchanges << 1) {
                int   k1       = k + exchanges;
                float tmp_real = fact_real * _real[k1] - fact_imag * _imag[k1];
                float tmp_imag = fact_real * _imag[k1] + fact_imag * _real[k1];
                _real[k1] = _real[k] - tmp_real;
                _imag[k1] = _imag[k] - tmp_imag;
                _real[k] += tmp_real;
                _imag[k] += tmp_imag;
            }
        }
        exchanges <<= 1;
        factfact  >>= 1;
    }
}

void FFT::writeOutput(float* output) const {
    for (int i = 0; i <= kBufferSize / 2; ++i)
        output[i] = _real[i] * _real[i] + _imag[i] * _imag[i];
    output[0]              /= 4.0f;
    output[kBufferSize / 2] /= 4.0f;
}

void FFT::perform(const short* input, float* output) {
    prepare(input);
    calculate();
    writeOutput(output);
}

} // namespace Hunchback::Framework
