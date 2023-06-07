/**
 * File: src/mel_filter_banks.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Mel filter banks creation implementation.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "mel_filter_banks.h"

#include "mel_convert.h"

namespace specto_impl {

std::vector<std::vector<float>> makeMelFilterBanks(
    int numBanks, int numFreqBins, float samplingResolution) {
  std::vector<std::vector<float>> banks;
  banks.reserve(numBanks);
  for (int i = 0; i < numBanks; ++i) {
    banks.push_back(std::vector<float>(numFreqBins, 0.0f));
  }
  float maxHz = samplingResolution * numFreqBins;
  float maxMel = hzToMel(maxHz);
  // Since mel banks need to be spaced evenly on the edges too,
  // the delta is + 1
  float melDelta = maxMel / (numBanks + 1);
  // This value will move to leftMel boundary for each bank
  float leftMel = 0.0f;
  for (int bankI = 0; bankI < numBanks; ++bankI) {
    float leftHz = melToHz(leftMel);
    float rightMel = leftMel + melDelta * 2.0f;
    float rightHz = melToHz(rightMel);
    float centerMel = leftMel + melDelta;
    float centerHz = melToHz(centerMel);
    float upSlope = 1.0f / (centerHz - leftHz);
    float downSlope = -1.0f / (rightHz - centerHz);

    for (int hzBinI = 0; hzBinI < numFreqBins; ++hzBinI) {
      float freq = hzBinI * samplingResolution;
      if (freq >= leftHz && freq < centerHz) {
        banks[bankI][hzBinI] = (freq - leftHz) * upSlope;
      } else if (freq >= centerHz && freq < rightHz) {
        // Adding 1 to negative slope so this will be positive
        banks[bankI][hzBinI] = 1.0f + (freq - centerHz) * downSlope;
      }
    }
    leftMel += melDelta;
  }
  return banks;
}

}  // namespace specto_impl
