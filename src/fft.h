/**
 * File: src/fft.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: FFT algorithms interface.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <vector>

#include "AudioFile.h"

namespace specto_impl {

// Will return fft that is size N / 2 if N is even else N / 2 + 1
std::vector<float> fft(const std::vector<float>&);

}  // namespace specto_impl
