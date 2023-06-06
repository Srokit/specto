/**
 * File: test/src/fft_test.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Unit tests for fft algorithms.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "gtest/gtest.h"

#include <algorithm>
#include <cmath>
#include <vector>

#include "fft.h"

constexpr int kSampleRate = 44100;

std::vector<float> make1SecXHzSignal(float f) {
  constexpr float kDuration = 1.0f;
  int N = static_cast<int>(kSampleRate * kDuration);
  std::vector<float> signal;
  signal.reserve(N);
  for (int i = 0; i < N; i++) {
    signal.push_back(std::sin(f * 2.0f * M_PI * i / kSampleRate));
  }
  return signal;
}

TEST(FftTest, SingleProminantFreq) {
  auto input = make1SecXHzSignal(10.0f);
  auto result = specto_impl::fft(input);

  EXPECT_EQ(result.size(), input.size());

  // The 10Hz signal should be the most prominent and therefore largest value
  // is in that index.
  auto maxIter = std::max_element(result.begin(), result.end());
  auto maxI = std::distance(result.begin(), maxIter);

  EXPECT_EQ(maxI, 10);
}
