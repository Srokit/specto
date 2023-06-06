/**
 * File: src/mel_convert.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Mel scale helpers.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <cmath>
#include <vector>

namespace specto_impl {

/**
 * Equation used:
 *   mel = 2595.0 * np.log10(1.0 + f / 700.0)
 * 
 * From: https://librosa.org/doc/main/generated/librosa.mel_frequencies.html
*/

inline float melToFreq(float mel) {
  return 700.0f * (std::pow(10.0f, mel / 2595.0f) - 1.0f);
}

inline float freqToMel(float freq) {
  return 2595.0f * std::log10(1.0f + freq / 700.0f);
}

}  // namespace specto_impl
