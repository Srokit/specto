/**
 * File: src/hanning.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Hanning windowing function implementation.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "hanning.h"

#include <cmath>

namespace specto_impl {

void hanningInPlace(std::vector<float>* data) {
  for (int i = 0; i < data->size(); ++i) {
    float omeg = 2.0f * M_PI * i / (data->size() - 1);
    (*data)[i] *= 0.5f - 0.5f * std::cos(omeg);
  }
}

}  // namespace specto_impl
