/**
 * File: src/hanning.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Hanning windowing function.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <vector>

namespace specto_impl {

/**
 * Performs Hanning windowing in place.
 * Using algorithm from: https://numpy.org/doc/stable/reference/generated/numpy.hanning.html
 * Aka: A[i] *= 0.5 - 0.5 * cos(2 * pi * i / (N - 1))
 */
void hanningInPlace(std::vector<float>*);

}  // namespace specto_impl
