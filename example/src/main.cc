/**
 * File: example/src/main.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Main file for example program using specto.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include <iostream>

#include "specto/spectogram.h"

constexpr float kHopDurationSec = 10.0;
constexpr int kNumFreqBins = 128;
constexpr int kMinFreq = 20;
constexpr int kMaxFreq = 10000;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  std::string filename(argv[1]);
  std::cout << "Loading file: " << filename << std::endl;
  return 0;
}
