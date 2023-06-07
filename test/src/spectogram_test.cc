/**
 * File: test/src/spectogram_test.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Unit tests for the main Spectogram class of public API.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include <vector>

#include "gtest/gtest.h"

#include "specto/spectogram.h"

TEST(SpectogramTest, Dimensions) {
  const int kNumMelBins = 10;
  // Same as data size
  const int kSampleRate = 10;
  const std::vector<float> kInputData {1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                       6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  specto::Spectogram spectogram = specto::makeSpectogram({
    .windowLen = 2,
    .windowHop = 1,
    .numMelBins = kNumMelBins,
  });
  spectogram->loadDataWithSampleRate(kInputData, kSampleRate);
  // kExpNumWins = (dataSize - windowLen) / windowHop + 1
  const int kExpectedNumWindows = 9;

  EXPECT_EQ(spectogram->getNumWindows(), kExpectedNumWindows);
  EXPECT_EQ(spectogram->getNumFrequencyBins(), kNumMelBins);
}
