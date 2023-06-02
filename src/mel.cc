/**
 * File: src/mel.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Mel scale helpers implementation.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "mel.h"

namespace specto_impl {

std::vector<int> calcFreqBounds(
    CalcFreqBoundsOptions options) {
  std::vector<int> bounds(options.numBins);
  float melLow = freqToMel(options.minFreq);
  float melHigh = freqToMel(options.maxFreq);
  float deltaMel = (melHigh - melLow) / (options.numBins);
  // The bounds will start at the first bound after the minFreq.
  // Hence, the i = 1 and < opts.numBins + 1.
  for (int i = 1; i < options.numBins + 1; ++i) {
    bounds[i] = static_cast<int>(melToFreq(melLow + deltaMel * i));
  }
  return bounds;
}

}  // namespace specto_impl
