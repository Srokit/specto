/**
 * File: src/fft.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: FFT algorithms implementation.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "fft.h"

#include <cmath>

#include "fftw3.h"

namespace specto_impl {

std::vector<float> fft(const std::vector<float>& input) {
    size_t n = input.size();
    fftwf_complex* in = reinterpret_cast<fftwf_complex*>(
        fftwf_malloc(sizeof(fftwf_complex) * n));
    fftwf_complex* out = reinterpret_cast<fftwf_complex*>(
        fftwf_malloc(sizeof(fftwf_complex) * n));
    fftwf_plan plan = fftwf_plan_dft_1d(
        n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    for (size_t i = 0; i < n; i++) {
        in[i][0] = input[i];
        in[i][1] = 0;
    }
    fftwf_execute(plan);
    size_t final_fft_size = (n % 2 == 0) ? (n / 2) : (n / 2 + 1);
    std::vector<float> output(final_fft_size);
    for (size_t i = 0; i < final_fft_size; i++) {
        output[i] = std::sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
    }
    fftwf_destroy_plan(plan);
    fftwf_free(in);
    fftwf_free(out);
    return output;
}

}  // namespace specto_impl
