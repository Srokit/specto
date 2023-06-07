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

#include "ui.h"

void printSpecStats(const specto::Spectogram& spectogram) {
  std::cout << "Num Windows: " << spectogram->getNumWindows() << std::endl;
  std::cout << "Num Frequency Bins: " << spectogram->getNumFrequencyBins()
            << std::endl;
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
  printSpecStats(spectogram);
  example_ui::drawSpectogram(spectogram);
  return 0;
}
