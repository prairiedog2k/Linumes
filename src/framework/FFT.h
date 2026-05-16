#pragma once

#include <array>

namespace Hunchback::Framework {

// Fixed 512-point radix-2 Cooley-Tukey FFT.
// perform() accepts 512 signed 16-bit PCM samples and writes
// 257 power-spectrum values (magnitudeÂ²) to the output array.
class FFT {
public:
    static constexpr int kBufferSize = 512;

    FFT();

    void perform(const short* input, float* output);

private:
    std::array<unsigned int, kBufferSize>     _bitReverse;
    std::array<float,        kBufferSize / 2> _cosTable;
    std::array<float,        kBufferSize / 2> _sinTable;
    std::array<float,        kBufferSize>     _real;
    std::array<float,        kBufferSize>     _imag;

    void prepare(const short* input);
    void calculate();
    void writeOutput(float* output) const;
};

} // namespace Hunchback::Framework
