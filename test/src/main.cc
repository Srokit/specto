/**
 * File: test/src/main.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Main file to start unit tests.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "gtest/gtest.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
