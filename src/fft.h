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

std::vector<float> fft(float*, int);

}  // namespace specto_impl
