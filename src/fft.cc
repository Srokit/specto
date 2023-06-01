
#include "fft.h"

#include <fftw3.h>
#include <cmath>

std::vector<float> fft(float* input, int size) {
    std::vector<float> output(size);
    fftwf_complex* in = reinterpret_cast<fftwf_complex*>(
        fftwf_malloc(sizeof(fftwf_complex) * size));
    fftwf_complex* out = reinterpret_cast<fftwf_complex*>(
        fftwf_malloc(sizeof(fftwf_complex) * size));
    fftwf_plan plan = fftwf_plan_dft_1d(
        size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    for (int i = 0; i < size; i++) {
        in[i][0] = input[i];
        in[i][1] = 0;
    }
    fftwf_execute(plan);
    for (int i = 0; i < size; i++) {
        output[i] = std::sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
    }
    fftwf_destroy_plan(plan);
    fftwf_free(in);
    fftwf_free(out);
    return output;
}