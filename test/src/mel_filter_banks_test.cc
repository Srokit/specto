/**
 * File: test/src/mel_filter_banks_test.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Unit tests for Mel filter banks creation.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "gtest/gtest.h"

#include "mel_filter_banks.h"

constexpr float kAllowedDiff = 0.001f;
constexpr int kPeakSearchDistance = 5;
constexpr float kMinPeakVal = 0.95f;

void expectAllBetweenOAnd1(const std::vector<std::vector<float>>& banks) {
  for (int i = 0; i < banks.size(); i++) {
    for (int j = 0; j < banks[i].size(); j++) {
      EXPECT_GE(banks[i][j], 0.0f) <<
          "at (" << i << ", " << j << ") " << banks[i][j] << " is lt 0";
      EXPECT_LT(banks[i][j], 1.0f) <<
                "at (" << i << ", " << j << ") " << banks[i][j] << " is ge 1";
    }
  }
}

void expectPeaksToBeAt(
    const std::vector<std::vector<float>>& banks,
    const std::vector<int>& expectedPeaks) {
  for (int i = 0; i < expectedPeaks.size(); i++) {
    int peak = expectedPeaks[i];
    int bankI = i;
    int leftPeakI = peak - kPeakSearchDistance;
    int rightPeakI = peak + kPeakSearchDistance;
    EXPECT_GE(banks[bankI][peak], kMinPeakVal) <<
        "peak at (" << bankI << ", " << peak << ") val " << banks[bankI][peak] <<
        " is not ge min val " << kMinPeakVal;
    EXPECT_LT(banks[bankI][leftPeakI], banks[bankI][peak]) <<
        "leftOfPeak at (" << bankI << ", " << leftPeakI << ") val " << banks[bankI][leftPeakI] <<
        " is not lt expected peak at (" << bankI << ", " << peak << ") val " << banks[bankI][peak];
    EXPECT_LT(banks[bankI][rightPeakI], banks[bankI][peak]) <<
        "rightOfPeak at (" << bankI << ", " << rightPeakI << ") val " << banks[bankI][rightPeakI] <<
        " is not lt expected peak at (" << bankI << ", " << peak << ") val " << banks[bankI][peak];
  }
}

TEST(MelFilterBanks, SimpleTest) {
  int numBanks = 4;
  int numFreqBins = 1000;
  float sampReso = 1.0f;
  /**
   * NOTE: All calculations done on Google search bar.
   * 
   * Based on above setup, the max mel = mel(1000hz) =~ 999.98 mel
   * Then the melDelta = 999.98 / (4 + 1) = 199.996
   * 
   * Therefore, the expected peaks are:
   *   (199.996) * 1 = 199.96 mel = 135.90 hz
   *   (199.996) * 2 = 399.92 mel = 298.18 hz
   *                              = 491.97 hz
   *                              = 723.38 hz
   * 
   * Round these down to the nearest integer.
   */
  std::vector<int> expectedPeaks {135, 298, 491, 723};

  auto banks = specto_impl::makeMelFilterBanks({
      .numBanks = numBanks,
      .numFreqBins = numFreqBins,
      .samplingResolution = sampReso
  });

  EXPECT_EQ(banks.size(), numBanks);
  EXPECT_EQ(banks[0].size(), numFreqBins);
  expectAllBetweenOAnd1(banks);
  expectPeaksToBeAt(banks, expectedPeaks);
}
