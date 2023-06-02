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

void printSpectogram(const specto::Spectogram& spectogram) {
  int numWindows = spectogram->getNumWindows();
  int numFrequencyBins = spectogram->getNumFrequencyBins();
  for (int windowIndex = 0; windowIndex < numWindows; windowIndex++) {
    for (int frequencyBinIndex = 0; frequencyBinIndex < numFrequencyBins;
         frequencyBinIndex++) {
      double dbfs = spectogram->getDBFSAtWindowIndexAndFrequencyBinIndex(
          windowIndex, frequencyBinIndex);
      std::cout << "Window: " << windowIndex << ", Frequency Bin: "
                << frequencyBinIndex << ", DBFS: " << dbfs << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  std::string filename(argv[1]);
  std::cout << "Loading file: " << filename << std::endl;

  specto::Spectogram spectogram = specto::makeSpectogram();
  spectogram->loadFile(filename);
  printSpectogram(spectogram);
  return 0;
}
