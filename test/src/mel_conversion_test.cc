/**
 * File: test/src/mel_test.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Unit tests for mel conversion helpers.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include <array>
#include <tuple>

#include "gtest/gtest.h"

#include "mel_convert.h"

static constexpr std::array<std::tuple<float, float>, 5> getMelToFreqTcs() {
  /**
   * Values taken from University College London:
   * http://www.homepages.ucl.ac.uk/~sslyjjt/speech/Mel2Hz.html
   * 
   * First val is Mel, second is freq in Hz.
  */
  return {
    std::make_tuple(1.0f, 0.6213878756400559f),
    std::make_tuple(10.0f, 6.238759792568627f),
    std::make_tuple(27.0f, 16.972525599711965f),
    std::make_tuple(1000.0f, 1000.0000004472436f),
    std::make_tuple(3000.0f, 9326.530620158375f),
  };
}

// Arbitrarily chosen
static constexpr float allowedDiff = 1.0f;

TEST(MelConversionTest, MelToFreqZero) {
  EXPECT_FLOAT_EQ(specto_impl::melToFreq(0.0f), 0.0f);
}

TEST(MelConversionTest, MelToFreqSimple) {
  for (auto [in, expected] : getMelToFreqTcs()) {
    EXPECT_NEAR(specto_impl::melToFreq(in), expected, allowedDiff);
  }
}

TEST(MelConversionTest, FreqToMelZero) {
  EXPECT_FLOAT_EQ(specto_impl::freqToMel(0.0f), 0.0f);
}

TEST(MelConversionTest, FreqToMelSimple) {
  // Opposite of above
  for (auto [expected, in] : getMelToFreqTcs()) {
    EXPECT_NEAR(specto_impl::freqToMel(in), expected, allowedDiff);
  }
}
