/**
 * File: src/mel.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Mel scale helpers interface.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <cmath>
#include <vector>

namespace specto_impl {

struct CalcFreqBoundsOptions {
  int numBins;
  int minFreq;
  int maxFreq;
};

std::vector<int> calcFreqBounds(
  CalcFreqBoundsOptions options);

inline float melToFreq(float mel) {
  return 700.0f * (std::expf(mel / 1127.0f) - 1.0f);
}

inline float freqToMel(float freq) {
  return 1127.0f * std::log1pf(freq / 700.0f);
}

}  // namespace specto_impl
