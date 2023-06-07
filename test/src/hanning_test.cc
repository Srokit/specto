/**
 * File: test/src/hanning_test.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Unit tests for the hanning window function.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "gtest/gtest.h"

#include "hanning.h"

constexpr float kAllowedDiff = 0.001f;

TEST(HanningTest, SuperSmall) {
  std::vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f};
  std::vector<float> expected = {0.0f, 1.5f, 2.25f, 0.0f};

  specto_impl::hanningInPlace(&input);

  EXPECT_EQ(input.size(), expected.size());

  for (int i = 0; i < input.size(); i++) {
    EXPECT_NEAR(input[i], expected[i], kAllowedDiff);
  }
}