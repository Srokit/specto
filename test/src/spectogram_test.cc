/**
 * File: test/src/spectogram_test.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Unit tests for the main Spectogram class of public API.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include <cmath>
#include <vector>

#include "gtest/gtest.h"

#include "specto/spectogram.h"

// Datasize is also the samplerate for default
const int kDefaultDataSize = 100;
const int kDefaultWinLen = 10;
const int kDefaultHopSize = 5;
// kExpNumWins = (dataSize - windowLen) / windowHop + 1
// = (100 - 10) / 5 + 1 = 19
const int kDefaultExpectedNumWindows = 19;
const int kDefaultNumMelBins = 10;

std::vector<float> makeXHzSinWave(float x, int sampleRate, int numSamples) {
  std::vector<float> data(numSamples, 0.0f);
  for (int i = 0; i < numSamples; ++i) {
    data[i] = std::sin(2.0f * M_PI * x * i / sampleRate);
  }
  return data;
}

specto::Spectogram makeDefaultSpectogram() {
  // Samplerate and datasize are same
  const std::vector<float> kInputData = makeXHzSinWave(
      5.0f, kDefaultDataSize, kDefaultDataSize);
  specto::Spectogram spectogram = specto::makeSpectogram({
    .windowLen = kDefaultWinLen,
    .windowHop = kDefaultHopSize,
    .numMelBins = kDefaultNumMelBins,
  });
  spectogram->loadDataWithSampleRate(kInputData, kDefaultDataSize);
  return spectogram;
}

TEST(SpectogramTest, Dimensions) {
  // Same as data size
  auto spectogram = makeDefaultSpectogram();

  EXPECT_EQ(spectogram->getNumWindows(), kDefaultExpectedNumWindows);
  EXPECT_EQ(spectogram->getNumFrequencyBins(), kDefaultNumMelBins);
}

TEST(SpectogramTest, Between0And1Inclusive) {
  auto spectogram = makeDefaultSpectogram();
  for (int i = 0; i < spectogram->getNumWindows(); i++) {
    for (int j = 0; j < spectogram->getNumFrequencyBins(); j++) {
      EXPECT_GE(spectogram->getDBFSAtWindowIndexAndFrequencyBinIndex(i, j), 0.0f);
      EXPECT_LE(spectogram->getDBFSAtWindowIndexAndFrequencyBinIndex(i, j), 1.0f);
    }
  }
}
